let component = ReasonReact.statelessComponent("TodoApp");

let make = (children) => {
  ...component,
  render: (self) =>
    <div className="app">
      <div className="title"> (ReasonReact.stringToElement("What to do")) </div>
      <div className="items"> (ReasonReact.stringToElement("Nothing")) </div>
    </div>
};
