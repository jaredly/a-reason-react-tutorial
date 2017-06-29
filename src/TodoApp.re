
type item = {
  title: string,
  completed: bool,
};
type state = {
  items: list item,
};

let component = ReasonReact.statefulComponent "TodoList";

/* I've gone ahead and made a shorted name for converting strings to elements
 * */
let se = ReasonReact.stringToElement;
let make children => {
  ...component,
  initialState: fun () => {
    items: [{
      title: "Write some things to do",
      completed: false,
    }]
  },
  render: fun {items} self => {
    let numItems = List.length items;
    let itemToAdd = {title: "Click a button", completed: true};
    <div className="app">
      <div className="title">
        (se "What to do")
        <button
          onClick=(self.update (fun evt state self => {
            ReasonReact.Update {
              ...state,
              items: [itemToAdd, ...state.items]
            }
          }))
        >
          (se "Add something")
        </button>
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

/*
        (ReasonReact.arrayToElement
          (Array.of_list renderedItems))
    let renderedItems = List.map
      (fun {title, completed} => se title)
      items;

  type show =
    | All
    | Completed
    | NotCompleted;
    */
