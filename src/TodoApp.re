
/* I've gone ahead and made a shorted name for converting strings to elements
 * */
let se = ReasonReact.stringToElement;

type item = {
  title: string,
  completed: bool,
};

let module TodoItem = {
  let component = ReasonReact.statelessComponent "TodoItem";
  let make ::item children => {
    ...component,
    render: fun () _ => {
      <div className="item">
        <input
          _type="checkbox"
          className="checkbox"
          checked=(Js.Boolean.to_js_boolean item.completed)
          /* TODO make interactive */
        />
        (se item.title)
      </div>
    }
  };
};

type state = {
  items: list item,
};

let component = ReasonReact.statefulComponent "TodoList";

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

    let renderedItems = List.map
    (fun item => <TodoItem item />)
    items;

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
        (numItems === 0
          ? se "Nothing"
          : ReasonReact.arrayToElement (Array.of_list renderedItems))
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
