
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

let component = ReasonReact.statelessComponent "TicTacToe";

let make children => {
  ...component,
  render: fun () self => {
    <div className="helloWorld">
      (ReasonReact.stringToElement "Hello World")
      <Tile number=2 />
    </div>
  }
};

