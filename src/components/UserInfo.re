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
             | NoData =>
               <div className="alert alert-warning" role="alert">
                 (ReasonReact.string("No Data received"))
               </div>
             | Loading => ReasonReact.null
             | Error(_error) =>
               <div className="alert alert-danger" role="alert">
                 (
                   ReasonReact.string(
                     "An unexpeced error occured, please try again later!",
                   )
                 )
               </div>
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