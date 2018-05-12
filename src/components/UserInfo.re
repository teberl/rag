[%bs.raw {|require('./UserInfo.css')|}];

module UserInfoQuery = [%graphql
  {|
    query {
      viewer {
        login
        name
        location
      }
    }
|}
];

module GetUserInfo = ReasonApollo.CreateQuery(UserInfoQuery);

let component = ReasonReact.statelessComponent("UserInfo");

let make = _children => {
  ...component,
  render: _self => {
    let userInfoQuery = UserInfoQuery.make();
    <GetUserInfo variables=userInfoQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => <div> (ReasonReact.string("No Viewer Data")) </div>
             | Loading => <div> (ReasonReact.string("Loading ...")) </div>
             | Error(_error) => <div> (ReasonReact.string("Error")) </div>
             | Data(response) =>
               <div
                 className="UserInfo-alert alert alert-success" role="alert">
                 (ReasonReact.string("Signed in as "))
                 <b> (ReasonReact.string(response##viewer##login)) </b>
               </div>
             }
         )
    </GetUserInfo>;
  },
};