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

let valueFromEvent evt: string =>
  (evt
    |> ReactEventRe.Form.target
    |> ReactDOMRe.domElementToObj
  )##value;

let module Input = {
  type state = string;
  let component = ReasonReact.statefulComponent "Input";
  let make ::onSubmit _ => {
    ...component,
    initialState: fun () => "",
    render: fun {state: text, update} =>
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(update (fun evt _ =>
          ReasonReact.Update (valueFromEvent evt)
        ))
        onKeyDown=(update (fun evt {state: text} =>
          if (ReactEventRe.Keyboard.key evt == "Enter") {
            onSubmit text;
            ReasonReact.Update "";
          } else {
            ReasonReact.NoUpdate
          }
        ))
      />
  };
};

type state = {
  items: list item,
};

let component = ReasonReact.statefulComponent "TodoApp";

let lastId = ref 0;
let newItem text => {
  lastId := !lastId + 1;
  {id: !lastId, title: text, completed: false};
};

let toggleItem items id => {
  List.map
  (fun item => item.id === id ? {...item, completed: not item.completed} : item)
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
        <Input
          onSubmit=(update (fun text {state} => {
            ReasonReact.Update {
              ...state,
              items: [newItem text, ...state.items]
            }
          }))
        />
      </div>
      <div className="items">
        (ReasonReact.arrayToElement
          (Array.of_list
            (List.map (fun item => <TodoItem
              key=(string_of_int item.id)
              onToggle=(update (fun () {state} =>
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