[%bs.raw {|require('./Header.css')|}];

[@bs.module] external logo : string = "../image/logo.svg";

type state = {collapsed: bool};

type action =
  | Click;

let component = ReasonReact.reducerComponent("Header");

let make = _children => {
  ...component,
  initialState: () => {collapsed: true},
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({collapsed: ! state.collapsed})
    },
  render: ({send, state}) => {
    let isCollapsed = state.collapsed ? "" : "show";
    <header>
      <div className=("bg-dark collapse" ++ isCollapsed) id="navbarHeader">
        <div className="container">
          <div className="row">
            <div className="col-sm-8 col-md-7 py-4">
              <h4 className="text-white"> (ReasonReact.string("About")) </h4>
              <p className="text-muted">
                (
                  ReasonReact.string(
                    "Started by a GraphQL & ReasonML workshop at ReasonConf 2018 in Vienna. The project is about exploring the Github API v4 in combination with Reason-Apollo and ReasonML.",
                  )
                )
                <br />
                (ReasonReact.string("To get started, have a looke at"))
                <br />
                <code>
                  (
                    ReasonReact.string(
                      "https://developer.github.com/v4/explorer/",
                    )
                  )
                </code>
                <br />
                <code>
                  (
                    ReasonReact.string(
                      "https://github.com/apollographql/reason-apollo",
                    )
                  )
                </code>
              </p>
            </div>
            <div className="col-sm-4 offset-md-1 py-4">
              <h4 className="text-white">
                (ReasonReact.string("Contact"))
              </h4>
              <ul className="list-unstyled">
                <li>
                  <a href="#" className="text-white">
                    (ReasonReact.string("Follow on Twitter"))
                  </a>
                </li>
                <li>
                  <a href="#" className="text-white">
                    (ReasonReact.string("Star on Github"))
                  </a>
                </li>
                <li>
                  <a href="#" className="text-white">
                    (ReasonReact.string("Send a message over discord"))
                  </a>
                </li>
              </ul>
            </div>
          </div>
        </div>
      </div>
      <div className="navbar navbar-dark bg-dark box-shadow">
        <div className="container d-flex justify-content-between">
          <a href="#" className="navbar-brand d-flex align-items-center">
            <img src=logo className="Header-logo" alt="reason-logo" />
            <strong> (ReasonReact.string("R:A:G")) </strong>
          </a>
          <button
            className="navbar-toggler collapsed"
            _type="button"
            onClick=(_event => send(Click))>
            <span className="navbar-toggler-icon" />
          </button>
        </div>
      </div>
    </header>;
  },
};