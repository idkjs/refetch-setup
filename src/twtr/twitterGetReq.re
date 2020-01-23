open Resync;
open Refetch;

include IsoFetch;
let consumer_key = "bDVlFjkYD7v4WkKIuu5AbCjSr";
let consumer_secret = "J2tALuP5nuGzuc1mtZ281tOlRnGW5Vp5fPprYUT2xSVwpNJ2Is";
let requestTokenURL = "https://api.twitter.com/oauth/request_token";

type oAuthConfig = {
  .
  callback: string,
  consumer_key: string,
  consumer_secret: string,
};
let oAuthConfig = {
  "callback": "oob",
  "consumer_key": consumer_key,
  "consumer_secret": consumer_secret,
};
type oauth = {
  .
  callback: string,
  consumer_key: string,
  consumer_secret: string,
};
let oauth = {
  "oauth": {
    callback: "oob",
    consumer_key,
    consumer_secret,
  },
};
external toJson: 'a => Js.Json.t = "%identity";

let oauthJson = oauth##oauth;
Js.log2("oauthJson", oauthJson);
type requestTokenJson = {
  .
  "url": string,
  "oauth": Js.t(Js.Json.t),
};
let requestTokenJson = {"url": requestTokenURL, "oauth": oauthJson};
Js.log2("requestTokenJson", requestTokenJson);
let oAuthConfigJson = requestTokenJson->toJson;
Js.log2("oAuthConfigJson", oAuthConfigJson);
/* async function requestToken() {
     const oAuthConfig = {
       callback: "oob",
       consumer_key: consumer_key,
       consumer_secret: consumer_secret
     };

     const req = await post({ url: requestTokenURL, oauth: oAuthConfig });
     if (req.body) {
       return qs.parse(req.body);
     } else {
       throw new Error("Cannot get an OAuth request token");
     }
   } */

let options: Readline.interfaceOptions = {
  input: [%raw "process.stdin"],
  output: [%raw "process.stdout"],
  terminal: None,
  historySize: None,
  prompt: None,
  crlfDelay: None,
  removeHistoryDuplicates: None,
};

let readline = Readline.createInterface(options);
let read = Readline.question(readline, "cli> ");
let rec cli = () => {
  read(line => {
    line |> Js.log2("line", _) |> ignore;
    cli();
  });
};
request(`POST, requestTokenURL)
|> Request.payload(`Json(oAuthConfigJson))
|> fetch
|> Future.flatMap(
     fun
     | Response.Ok(_, response) => Response.text(response)
     | Response.Error({reason}, _) => Future.from(reason),
   )
|> Future.whenResolved(Js.log) /*    )*/ /*      | Error(e) => Js.log(e)*/;

// get("http://httpbin.org/image/png")
// |> Future.map(
//      fun
//      | Response.Ok(_, response) => Response.body(response)
//      | Response.Error({reason}, _) => failwith(reason),
//    )
// |> Future.whenCompleted(
//      fun
//      | Ok(stream) =>
//        streamToBuffer(stream, (_, buffer) =>
//          stringifyPng(buffer, (_, string) => Js.log(string))
//        )