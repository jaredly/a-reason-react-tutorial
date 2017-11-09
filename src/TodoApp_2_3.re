type item = {
  id: int,
  title: string,
  completed: bool
};

let se = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (_) =>
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

let lastId = ref(0);

let newItem = () => {
  lastId := lastId^ + 1;
  {id: lastId^, title: "Click a button", completed: true}
};

let make = (children) => {
  ...component,
  initialState: () => {items: [{id: 0, title: "Write some things to do", completed: false}]},
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
        (
          ReasonReact.arrayToElement(
            Array.of_list(
              List.map((item) => <TodoItem key=(string_of_int(item.id)) item />, items)
            )
          )
        )
      </div>
      <div className="footer"> (se(string_of_int(numItems) ++ " items")) </div>
    </div>
  }
};
