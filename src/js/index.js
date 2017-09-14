var Module = {};

const reset = document.getElementById('reset');
reset.addEventListener('click', ()=> location.reload());

Module.onAbort = () => {
  alert("it seems wasm doesn't work on your computer");
};
Module.onRuntimeInitialized = ()=> {
  const createMineField = Module.cwrap('createMineField','undefined', ['number', 'number', 'number']);
  const revealLocation = Module.cwrap('revealLocation','number', ['number', 'number']);
  const viewBoard = Module.cwrap('viewBoard','string', null);
  const addMines = Module.cwrap('addMines', 'number', ['number', 'number']);
  const revealAllMines = Module.cwrap('revealAllMines', 'undefined', null);

  const createFieldSection = document.querySelector('.createfield');
  const createFieldBtn = document.querySelector(".createfield > button");
  let width, height, minecount, board;
  createFieldBtn.addEventListener("click", ()=> {
    let inputs = document.querySelectorAll(".createfield input");
    height = parseInt(inputs[0].value);
    width = parseInt(inputs[1].value);
    minecount = parseInt(inputs[2].value);
    if (height < 4 || width < 4) {
      alert("minefield too small");
    } else if (height * width - 9 < minecount) {
      alert("more mines then field can hold");
    } else {
      createMineField(height, width, minecount);
      createFieldSection.style.display = "none";
      board = viewBoard();
      createBoard(height, width, board);
      reset.style.display = "block";
    }
  });
  let gameOver = false, gameStarted = false;
  let table = document.querySelector('table');
  table.addEventListener("click", function() {
    let minefield = event.target;
    let x = parseInt(minefield.getAttribute("data-x"));
    let y = parseInt(minefield.getAttribute("data-y"));
    if (!gameStarted) {
      addMines(x, y);
      gameStarted = true;
    }
    let revealed = minefield.getAttribute("data-revealed");
    if (revealed === "0" && !gameOver) {
      let isMineHit = revealLocation(x,y);
      board = viewBoard();
      let mineArray = splitBoardStr(board, width);
      displayBoard(width, mineArray);

      if (isMineHit) { // mine hit
        alert("Mine hit!");
        gameOver = true;
        let mineHitText = document.createTextNode("X");
        minefield.appendChild(mineHitText);
        minefield.classList.add("hit");
        revealAllMinesForGameOver(mineArray);
      } else {
        let hiddenFields = Array.from(document.querySelectorAll('td[data-revealed^="0"]'));
        let win = hiddenFields.every((field)=> {
          let x = parseInt(field.getAttribute("data-x"));
          let y = parseInt(field.getAttribute("data-y"));
          let mine = mineArray[x][y];
          return mine[0] === "9";
        });
        if (win)  {
          alert("You win");
          revealAllMinesForGameOver(mineArray);
          gameOver = true;
        }
      }
    }
  });
};

const revealAllMinesForGameOver = (mineArray) => {
  let hiddenFields = Array.from(document.querySelectorAll('td[data-revealed^="0"]'));
  hiddenFields.forEach((field) => {
    field.setAttribute("data-revealed", "1");
    let x = parseInt(field.getAttribute("data-x"));
    let y = parseInt(field.getAttribute("data-y"));
    let mine = mineArray[x][y];
    let mineHitText = document.createTextNode((mine[0] === "9") ? "X" : mine[0]);
    field.innerHTML = "";
    field.appendChild(mineHitText);
  });
};

const displayBoard = (width, mineArray) => {
  let rows = Array.from(document.querySelectorAll("tr"));
  rows.forEach((row, h)=> {
    Array.from(row.children).forEach((cell, w)=> {
      let mine = mineArray[w][h];
      if (mine[1] === "1" && cell.getAttribute("data-revealed") !== "1") {
        if (mine[0] !== "0") {
          let mineCount = document.createTextNode(mine[0]);
          cell.appendChild(mineCount);
        }
        cell.setAttribute("data-revealed", "1");
      }
    });
  });
}

const createBoard = (height, width, board) => {
  let mineArray = splitBoardStr(board, width);
  let docfragment = document.createDocumentFragment();
  for (let h = 0; h < height; h++) {
    let row = document.createElement("tr");
    for (let w = 0; w < width; w++) {
      let cell = document.createElement("td");
      let mine = mineArray[w][h];
      cell.setAttribute("data-x", w);
      cell.setAttribute("data-y", h);
      cell.setAttribute("data-revealed", mine[1]);
      row.appendChild(cell);
    }
    docfragment.appendChild(row);
  }
  let table = document.querySelector('table');
  table.appendChild(docfragment);
}

const splitBoardStr = (board, width)=>{
  let mineArray = [], mineGrid = [];
  let currBoard = board;
  do {
    let mine = currBoard.substr(0,2);
    currBoard = currBoard.substr(2);
    mineArray.push(mine);
  } while (currBoard !== "");
  while(mineArray.length) mineGrid.push(mineArray.splice(0, width)); // convert to 2d array
  return mineGrid;
}
