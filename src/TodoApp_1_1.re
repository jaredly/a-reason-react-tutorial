type item = {
  title: string,
  completed: bool,
};
type state = {
  /* this is a type w/ a type argument,
   * similar to List<Item> in TypeScript,
   * Flow, or Java */
  items: list item,
};

let component = ReasonReact.statefulComponent "TodoApp";

/* I've gone ahead and made a shortened name for converting strings to elements */
let se = ReasonReact.stringToElement;
let make children => {
  ...component,
  initialState: fun () => {
    items: [{
      title: "Write some things to do",
      completed: false,
    }]
  },
  render: fun {state: {items}} => {
    let numItems = List.length items;
    <div className="app">
      <div className="title">
        (se "What to do")
      </div>
      <div className="items">
        (se "Nothing")
      </div>
      <div className="footer">
        (se ((string_of_int numItems) ^ " items"))
      </div>
    </div>
  }
};