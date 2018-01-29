type item = {
  id: int,
  title: string,
  completed: bool
};

type state = {items: list(item)};

let str = ReasonReact.stringToElement;

let pluralize = (str, ending, n) => str ++ (n === 1 ? "" : ending);

let pluralizeItems = pluralize("item", "s");

let valueFromEvent = evt : string => (
                                       evt
                                       |> ReactEventRe.Form.target
                                       |> ReactDOMRe.domElementToObj
                                     )##value;

type action =
  | AddItem(string)
  | ToggleItem(int);

module Input = {
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText),
    render: self =>
      <input
        _type="text"
        placeholder="Write something to do"
        onChange=(_evt => self.send(valueFromEvent(_evt)))
        onKeyDown=(
          _evt =>
            if (ReactEventRe.Keyboard.key(_evt) == "Enter") {
              onSubmit(self.state);
              self.send("");
            }
        )
        value=self.state
      />
  };
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, children) => {
    ...component,
    render: (_) =>
      <div className="item">
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
          onClick=(_evt => onToggle())
        />
        (str(item.title))
      </div>
  };
};

let component = ReasonReact.reducerComponent("TodoApp");

let newItem =
  (
    () => {
      let lastId = ref(-1);
      title => {
        lastId := lastId^ + 1;
        {id: lastId^, title, completed: false};
      };
    }
  )
    ();

let make = (_) => {
  ...component,
  initialState: () => {items: []},
  reducer: (action, {items}) =>
    switch action {
    | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
    | ToggleItem(id) =>
      items
      |> List.map(item =>
           item.id === id ? {...item, completed: ! item.completed} : item
         )
      |> (items => ReasonReact.Update({items: items}))
    },
  render: self => {
    let numItems = List.length(self.state.items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <Input onSubmit=(text => self.send(AddItem(text))) />
      </div>
      <div className="items">
        (
          self.state.items
          |> List.map(item =>
               <TodoItem
                 key=(string_of_int(item.id))
                 onToggle=(_event => self.send(ToggleItem(item.id)))
                 item
               />
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " " ++ pluralizeItems(numItems)))
      </div>
    </div>;
  }
};
