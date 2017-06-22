
let module Tile = {
  let component = ReasonReact.statelessComponent "Tile";

  let make ::number children => {
    ...component,
    render: fun () self => {
      <div className="tile">
        (ReasonReact.stringToElement (string_of_int number))
      </div>
    }
  };
};

let module Board = {
  let component = ReasonReact.statelessComponent "Board";

  let make children => {
    ...component,
    render: fun () self => {
      let renderTile number => <Tile number />;
      <div className="board">
        <div className="row">
          (renderTile 0)
          (renderTile 1)
          (renderTile 2)
        </div>
        <div className="row">
          (renderTile 3)
          (renderTile 4)
          (renderTile 5)
        </div>
        <div className="row">
          (renderTile 6)
          (renderTile 7)
          (renderTile 8)
        </div>
      </div>
    },
  };
};

let component = ReasonReact.statelessComponent "TicTacToe";

let make children => {
  ...component,
  render: fun () self => {
    <div className="helloWorld">
      (ReasonReact.stringToElement "Hello World")
      <Board />
    </div>
  }
};

