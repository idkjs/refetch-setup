type t;

type interfaceOptions = {
  input: in_channel,
  output: option(out_channel),
  terminal: option(bool),
  historySize: option(int),
  prompt: option(string),
  crlfDelay: option(int),
  removeHistoryDuplicates: option(int),
};

[@bs.module "readline"]
external createInterface: interfaceOptions => t = "createInterface";

[@bs.send]
external on:
  (
    t,
    [@bs.string] [
      | `close(unit => unit)
      | `line(string => unit)
      | `pause(unit => unit)
      | `resume(unit => unit)
      | `SIGCONT(unit => unit)
      | `SIGINT(unit => unit)
      | `SIGTSTP(unit => unit)
    ]
  ) =>
  t =
  "on";

[@bs.send] external close: t => unit = "close";

[@bs.send] external pause: t => unit = "pause";

[@bs.send]
external prompt: (t, ~preserveCursor: bool=?, unit) => unit = "prompt";

[@bs.send] external question: (t, string, string => unit) => unit = "question";

[@bs.send] external resume: t => unit = "resume";

[@bs.send] external setPrompt: (t, string) => unit = "setPrompt";

type keyOption = {
  ctrl: option(bool),
  meta: option(bool),
  shift: option(bool),
  name: string,
};

[@bs.send] external write: (t, ~key: keyOption=?, unit) => unit = "write";