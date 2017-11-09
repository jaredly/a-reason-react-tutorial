type item = {
  title: string,
  completed: bool
};

let se = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (self) =>
      <div className="item">
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
          /* TODO make interactive */
        />
        (se(item.title))
      </div>
  };
};

type state = {items: list(item)};

let component = ReasonReact.statefulComponent("TodoApp");

let newItem = () => {title: "Click a button", completed: true};

let make = (children) => {
  ...component,
  initialState: () => {items: [{title: "Write some things to do", completed: false}]},
  render: ({state: {items}, update}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (se("What to do"))
        <button
          onClick=(
            update(
              (evt, {state}) => ReasonReact.Update({...state, items: [newItem(), ...state.items]})
            )
          )>
          (se("Add something"))
        </button>
      </div>
      <div className="items">
        (ReasonReact.arrayToElement(Array.of_list(List.map((item) => <TodoItem item />, items))))
      </div>
      <div className="footer"> (se(string_of_int(numItems) ++ " items")) </div>
    </div>
  }
};
