type state = {
  firstValue: int,
  direction: RepositoryList.orderDirection,
  first: int,
};

type action =
  | ChangeItemsCount(int)
  | ChangeDirection(RepositoryList.orderDirection)
  | UpdateList
  | KeyDown(int);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {firstValue: 5, first: 5, direction: `DESC},
  reducer: (action, state) =>
    switch (action) {
    | ChangeItemsCount(newValue) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, firstValue: newValue},
        (
          ({state}) =>
            Js.Console.log(
              "CurrentinputValue: " ++ string_of_int(state.firstValue),
            )
        ),
      )
    | ChangeDirection(newDirection) =>
      ReasonReact.Update({...state, direction: newDirection})
    | UpdateList => ReasonReact.Update({...state, first: state.firstValue})
    | KeyDown(27) => ReasonReact.Update({...state, firstValue: state.first})
    | KeyDown(13) => ReasonReact.Update({...state, first: state.firstValue})
    | KeyDown(_) => ReasonReact.NoUpdate
    },
  render: ({state, send}) =>
    <div className="container">
      <h2> (ReasonReact.string("Repository List")) </h2>
      <div>
        <div className="form-group mt-3 mb-3">
          <label>
            (
              ReasonReact.string(
                "Number of Repositories displayed ordered by stars",
              )
            )
          </label>
          <input
            _type="number"
            className="form-control"
            onChange=(
              event => {
                let trimmedEventValue =
                  String.trim(
                    ReactDOMRe.domElementToObj(
                      ReactEventRe.Form.target(event),
                    )##value,
                  );
                switch (trimmedEventValue) {
                | "" => send(ChangeItemsCount(0))
                | nonEmptyValue =>
                  send(ChangeItemsCount(int_of_string(nonEmptyValue)))
                };
              }
            )
            onBlur=(_event => send(UpdateList))
            onKeyDown=(
              event => send(KeyDown(ReactEventRe.Keyboard.which(event)))
            )
            value=(string_of_int(state.firstValue))
          />
        </div>
        <div className="form-group mt-3">
          <div className="form-check">
            <input
              className="form-check-input"
              _type="radio"
              name="direction"
              id="directionDesc"
              value="desc"
              defaultChecked=(state.direction === `DESC)
              onClick=(_event => send(ChangeDirection(`DESC)))
            />
            <label className="form-check-label" htmlFor="directionDesc">
              (ReasonReact.string("Descending"))
            </label>
          </div>
          <div className="form-check">
            <input
              className="form-check-input"
              _type="radio"
              name="direction"
              id="directionAsc"
              value="asc"
              defaultChecked=(state.direction === `ASC)
              onClick=(_event => send(ChangeDirection(`ASC)))
            />
            <label className="form-check-label" htmlFor="directionAsc">
              (ReasonReact.string("Ascending"))
            </label>
          </div>
        </div>
      </div>
      <RepositoryList first=state.first direction=state.direction />
    </div>,
};