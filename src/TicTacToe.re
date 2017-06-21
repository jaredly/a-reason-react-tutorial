
let component = ReasonReact.statelessComponent "TicTacToe";
let make _children => {
  ...component,
  render: fun () _self => {
    <div className="helloWorld">
      (ReasonReact.stringToElement "Hello World")
    </div>
  }
};

