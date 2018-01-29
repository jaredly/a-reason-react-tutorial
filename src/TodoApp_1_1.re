type item = {
  title: string,
  completed: bool
};

type state = {
  /* this is a type w/ a type argument,
   * similar to List<Item> in TypeScript,
   * Flow, or Java */
  items: list(item)
};

let component = ReasonReact.reducerComponent("TodoApp");

/* I've gone ahead and made a shortened name for converting strings to elements */
let str = ReasonReact.stringToElement;

let make = children => {
  ...component,
  initialState: () => {
    items: [{title: "Write some things to do", completed: false}]
  },
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: ({state: {items}}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title"> (str("What to do")) </div>
      <div className="items"> (str("Nothing")) </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>;
  }
};
