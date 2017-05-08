var Module = {};
Module.onRuntimeInitialized = ()=> {
  const createMineField = Module.cwrap('createMineField','undefined', ['number', 'number', 'number']);
  const revealLocation = Module.cwrap('revealLocation','number', ['number', 'number']);
  const viewBoard = Module.cwrap('viewBoard','string', null);
  const addMines = Module.cwrap('addMines', 'number', ['number', 'number']);

  const createFieldSection = document.querySelector('.createfield');
  const createFieldBtn = document.querySelector(".createfield > button");
  let width, height, minecount, board;
  createFieldBtn.addEventListener("click", ()=> {
    let inputs = document.querySelectorAll(".createfield input");
    height = parseInt(inputs[0].value);
    width = parseInt(inputs[1].value);
    minecount = parseInt(inputs[2].value);
    if (height * width - 9 >= minecount) {
      createMineField(height, width, minecount);
      createFieldSection.style.display = "none";
      board = viewBoard();
      createBoard(height, width, board);
    } else {
      alert("more mines then field can hold");
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
      if (revealLocation(x,y)) { // mine hit
        alert("Mine hit!");
        GameOver = true;
        let mineHitText = document.createTextNode("X");
        minefield.appendChild(mineHitText);
        minefield.classList.add("hit");
      }
      board = viewBoard();
      let mineArray = splitBoardStr(board, width);
      displayBoard(width, mineArray);
      let hiddenFields = Array.from(document.querySelectorAll('td[data-revealed^="0"]'));
      let win = hiddenFields.every((field)=> {
        let x = parseInt(field.getAttribute("data-x"));
        let y = parseInt(field.getAttribute("data-y"));
        let mine = mineArray[x][y];
        return mine[0] === "9";
      });
      if (win)  {
        alert("You win");
        gameOver = true;
      }
    }
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
      let mine = mineArray[h][w];
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
