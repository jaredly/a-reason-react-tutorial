type item = {
  title: string,
  completed: bool
};

type state = {items: list(item)};

let component = ReasonReact.statefulComponent("TodoApp");

let newItem = () => {title: "Click a button", completed: true};

let se = ReasonReact.stringToElement;

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
      <div className="items"> (se("Nothing")) </div>
      <div className="footer"> (se(string_of_int(numItems) ++ " items")) </div>
    </div>
  }
};
