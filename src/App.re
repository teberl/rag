let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <div className="App">
      <UserInfo />
      <div className="container">
        <h2> (ReasonReact.string("Repository List")) </h2>
        <RepositoryList />
      </div>
    </div>,
};