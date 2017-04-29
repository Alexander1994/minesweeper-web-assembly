var Module = {};
Module.onRuntimeInitialized = ()=> {
  Module.ccall('createMineField','undefined', ['number', 'number', 'number'], [8,8,64]);
  Module.ccall('revealLocation','number', ['number', 'number'], [0,0]);

  const board = Module.ccall('viewBoard','string', null, null);

  console.log(board);
};
