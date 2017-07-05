type item = {
  id: int,
  title: string,
  completed: bool,
};

let se = ReasonReact.stringToElement;

let module TodoItem = {
  let component = ReasonReact.statelessComponent "TodoItem";
  let make ::item ::onToggle children => {
    ...component,
    render: fun _ =>
      <div className="item" onClick=(fun evt => onToggle())>
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean item.completed)
        />
        (se item.title)
      </div>
  };
};

type state = {
  items: list item,
};

let component = ReasonReact.statefulComponent "TodoApp";

let lastId = ref 0;
let newItem () => {
  lastId := !lastId + 1;
  {id: !lastId, title: "Click a button", completed: true};
};

let toggleItem items id => {
  List.map
  (fun item => item.id === id
    ? {...item, completed: not item.completed}
    : item)
  items;
};

let make children => {
  ...component,
  initialState: fun () => {
    items: [{
      id: 0,
      title: "Write some things to do",
      completed: false,
    }]
  },
  render: fun {state: {items}, update} => {
    let numItems = List.length items;

    <div className="app">
      <div className="title">
        (se "What to do")
        <button
          onClick=(update (fun evt {state} => {
            ReasonReact.Update {
              ...state,
              items: [newItem(), ...state.items]
            }
          }))
        >
          (se "Add something")
        </button>
      </div>
      <div className="items">
        (ReasonReact.arrayToElement
          (Array.of_list
            (List.map (fun item => <TodoItem
              key=(string_of_int item.id)
              onToggle=(update (fun _ {state} =>
                ReasonReact.Update {
                  ...state,
                  items: toggleItem items item.id
                }
              ))
              item
            />) items)
          )
        )
      </div>
      <div className="footer">
        (se ((string_of_int numItems) ^ " items"))
      </div>
    </div>
  }
};
