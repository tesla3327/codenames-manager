type cardType =
  | Hidden
  | Red
  | Blue
  | Neutral
  | Assassin;

type card = {
  word: string,
  cardType,
};

let makeCard = (~word="Default", ~cardType=Hidden, ()) => {cardType, word};

type t = array(array(card));

let make = () => Belt.Array.make(5, Belt.Array.make(5, makeCard()));

let getNextCardType = cardType =>
  switch (cardType) {
  | Hidden => Red
  | Red => Blue
  | Blue => Neutral
  | Neutral => Assassin
  | Assassin => Hidden
  };

let cycleCardType = (board, word) =>
  Belt.(
    Array.map(board, row =>
      Array.map(row, card =>
        if (card.word === word) {
          makeCard(
            ~word=card.word,
            ~cardType=getNextCardType(card.cardType),
            (),
          );
        } else {
          card;
        }
      )
    )
  );

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