type cardType =
  | Hidden
  | Red
  | Blue
  | Neutral
  | Assassin;

type card = {
  id: string,
  word: string,
  cardType,
};

let makeCard = (~word="", ~cardType=Hidden, id) => {id, cardType, word};

type t = array(array(card));

/* let make = () => Belt.Array.make(5, Belt.Array.make(5, makeCard()); */
let getNextCardType = cardType =>
  switch (cardType) {
  | Hidden => Red
  | Red => Blue
  | Blue => Neutral
  | Neutral => Assassin
  | Assassin => Hidden
  };

let updateCards = (func, board) =>
  Belt.(Array.map(board, row => Array.map(row, func)));

let cycleCardType = (board, id) =>
  updateCards(
    card =>
      if (card.id === id) {
        makeCard(
          ~word=card.word,
          ~cardType=getNextCardType(card.cardType),
          card.id,
        );
      } else {
        card;
      },
    board,
  );

let getId = (row, col) => string_of_int(row) ++ string_of_int(col);

let make_with_words = words =>
  Belt.Array.(
    map(range(0, 4), row =>
      map(
        range(0, 4),
        col => {
          let index = row * 5 + col;
          let id = getId(row, col);
          if (length(words) > index) {
            makeCard(~word=words[index], id);
          } else {
            makeCard(id);
          };
        },
      )
    )
  );