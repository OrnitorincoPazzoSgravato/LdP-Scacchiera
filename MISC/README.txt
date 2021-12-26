        1) player realizzati come structs: permette di distinguere umano e bot
        2) i pezzi come re, torre e pedone devono avere una entry: alreadyMoved -> per le regole speciali
        3) i player, realizzati in 2 structs, si alternano i turni tramite switch di flag (switch che aumenta il contatore turni,
        necessario nel caso di bot match per le mosse massime)
        4) dato che dobbiamo far muovere in modo casuale il bot, avremmo bisogno di prendere un pezzo a caso tra quelli che ha e muoverlo
        in una posizione legale a caso
            -> serve avere una funzione che per un determinato pezzo torna un array con tutte le possibili mosse nel corrente stato della
                partita (ES: funzione getLegalMoves())
                -> le mosse consentite devono essere una struct, indicante la nuova posizione e se qualche altro pezzo si deve spostare
                    (per cattura o mosse speciali tipo l'arrocco), ovviamente dobbiamo sapere dove stavano questi pezzi
                    N.B.! per l'arrocco ad esempio è necessario settare a false la flag che controlla se il re si deve ancora muovere
                    -> sarebbe utile avere una funzione update() per ogni mossa che si occupa di queste cose tramite puntatori:
                        | se non ci sono stati avvenimenti particolari allora easy, la funzione non farà nulla. Altrimenti se c'è stato, ad
                        | esempio un arrocco, allora aggiornerà lo stato dei pezzi per rifletterlo. Stesso discorso per il primo movimento di
                        | un pedone
            -> il bot sceglierà a caso un pezzo, richiederà la generazione del vettore di mosse e ne sceglierà una a caso
            -> il giocatore umano sceglierà da input un pezzo e il programma, generando il vettore di mosse, verifica se quella che
                l'utente intendeva eseguire è valida, cioè sta nell'array
        5) i pezzi li gestiamo con tipo classe madre GamePieces, in questo modo update può tranquillamente gestire la regola
        speciale: PROMOZIONE
            -> questa è tricky da gestire, dobbiamo fare in modo che nella funzione move() si vada a chiedere all'utente
            in cosa vuole promuovere il pezzo e, nel caso di un bot, farlo promuovere a uno a caso tra tutti i pezzi
        6) dobbiamo mettere un enforce per gestire lo scacco e questo è difficile da fare tbh
            -> potremmo gestirlo a livello di giocatore: inseriamo una entry "scacco" che obbliga a selezionare il re come pezzo
            all'interno della funzione move
            -> la parte complessa e riuscire a capire quando siamo in scacco, probabilmente conviene fare così: dopo ogni movimento di pezzo,
            lanciamo una chiamata alla funzione getLegalMoves() per ogni pezzo mosso e verifichiamo se ci sta il re tra i pezzi catturati
            in ogni mossa del vettore di mosse consentite, se ci sta allora aggiorniamo la flag di scacco.
            RIASSUNTO: il programma sta "giocando" un turno avanti essenzialmente, questo dovrebbe funzionare perchè il re inizialmente non
            è in scacco, ma può diventarlo solo una volta che un pezzo dell'avversario si muove
        7) dobbiamo impedire al re di mettersi in scacco da solo IMPORTANTE
        8) scaccomatto essenzialmente è uno scacco che non si risolve, ovvero uno scacco in cui ci troviamo un 0 mosse disponibili per il re
