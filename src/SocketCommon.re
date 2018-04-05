type t('a) =
  | Message;

let stringify = t =>
  switch (t) {
  | Message => "Message"
  };