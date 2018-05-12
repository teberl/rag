[@bs.module "./registerServiceWorker"]
external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Apollo.instance>
    <Header />
    <App />
  </ReasonApollo.Provider>,
  "root",
);

register_service_worker();