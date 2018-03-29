type cardType =
  | Red
  | Blue
  | Neutral
  | Assassin;

type card = {
  cardType,
  word: string,
  revealed: bool,
};

let makeCard = (~word="Default", ~cardType=Neutral, ~revealed=false, ()) => {
  cardType,
  word,
  revealed,
};

type t = array(array(card));

let make = () => Belt.Array.make(5, Belt.Array.make(5, makeCard()));

let make_with_words = words => {
  open Belt;
  let getRow = num =>
    Array.range(num * 5, num * 5 + 4)
    |> Array.map(_, index =>
         switch (words[index]) {
         | Some(word) => makeCard(~word, ())
         | None => makeCard()
         }
       );
  Array.range(0, 4) |> Array.map(_, getRow);
};

let changeCardType = (board, word, cardType) => {
  open Belt;
  /* Look in the first row */
  let firstRow =
    switch (board[0]) {
    | Some(row) => row
    | None => [||]
    };
  let matches = Array.keep(firstRow, word_ => word_ === word);
  ();
};