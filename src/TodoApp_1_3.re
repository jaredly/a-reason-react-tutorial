type item = {
  title: string,
  completed: bool
};

type state = {items: list(item)};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");

let newItem = () => {title: "Click a button", completed: true};

let str = ReasonReact.stringToElement;

let make = children => {
  ...component,
  initialState: () => {
    items: [{title: "Write some things to do", completed: false}]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
    },
  render: self => {
    let {items} = self.state;
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <button onClick=(_evt => self.send(AddItem))>
          (str("Add something"))
        </button>
      </div>
      <div className="items"> (str("Nothing")) </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>;
  }
};
