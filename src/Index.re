let words = [|
  "Date",
  "France",
  "Net",
  "Diamond",
  "Pass",
  "Knight",
  "Cross",
  "Tie",
  /* "Court",
     "Cotton",
     "Point",
     "Card",
     "Duck",
     "Star",
     "Slip",
     "Fighter",
     "Bridge",
     "Band",
     "Hood",
     "Olive",
     "Shop",
     "Match",
     "Ball",
     "Bow",
     "Mercury", */
|];

ReactDOMRe.renderToElementWithId(<BoardView words />, "app");