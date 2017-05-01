var Module = {};
Module.onRuntimeInitialized = ()=> {
  const createMineField = Module.cwrap('createMineField','undefined', ['number', 'number', 'number']);
  const revealLocation = Module.cwrap('revealLocation','number', ['number', 'number']);
  const viewBoard = Module.cwrap('viewBoard','string', null);

  const createFieldSection = document.querySelector('.createfield');
  const createFieldBtn = document.querySelector(".createfield > button");
  createFieldBtn.addEventListener("click", ()=> {
    let inputs = document.querySelectorAll(".createfield input");
    let height = inputs[0].value;
    let width = inputs[1].value;
    let minecount = inputs[2].value;
    createMineField(height, width, minecount);
    createFieldSection.style.display = "none";
    let board = viewBoard();
    createBoard(height, width, minecount, board);
  });
};

const createBoard = (height, width, minecount, board) => {
  let mineArray = splitBoardStr(board);
  let docfragment = document.createDocumentFragment();
  for (let h = 0; h < height; h++) {
    let row = document.createElement("tr");
    for (let w = 0; w < width; w++) {
      let cell = document.createElement("td");
      let mine = mineArray[w+h*width];
      if (mine[1] === "1") {
        console.log("mine is revealed");
      }
      let text = document.createTextNode(mine[0]);
      cell.appendChild(text);
      row.appendChild(cell);
    }
    docfragment.appendChild(row);
  }
  let table = document.querySelector('table');
  table.appendChild(docfragment);
}

const splitBoardStr = (board)=>{
  let mineArray = [];
  let currBoard = board;
  do {
    let mine = currBoard.substr(0,2);
    currBoard = currBoard.substr(2);
    mineArray.push(mine);
  } while (currBoard !== "");
  return mineArray;
}
