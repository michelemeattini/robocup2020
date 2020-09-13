# RoboCup 2020
 
Questa repository contiene il software più aggiornato sviluppato dal team _*Michele Meattini*_, Bilal Laasri, Mirko Soggetti, Pasquale de Roberto e Leonardo Crini per il robot *Mistake*.

In linea di massima funzionava ben sul robot cingolato. Il robot deve essere ben bilanciato per far si che questo codice funzioni bene. 
Se slitta e scivola in curva non è il software ma il robot non sbilanciato.

Il file Good Mistake.c è l'ultima bozza che abbiamo sviluppato, non è ottimizzata e si basa sulle funzioni che vengono importate dal file _function.h_.

La parte di raccogliere le palline nell'arena non è stata sviluppata per nulla.

La nostra idea era quella di utilizzare 2 arduini e farli comunicare in seriale, uno di essi poi avremme comunicato tutto all'EV3.
Alla fine abbiamo abbandonato l'idea ed abbiamo deciso che sarebbe bastato un arduino solo e al massimo il secondo solo per il giroscopio ma alla fine non l'abbiamo fatto.
Lo schema elettrico non è aggiornato, una cosa importante è mettere degli switch tra tx rx dei due arduini perchè altrimenti quando sono collegati non si può usare la seriale USB per caricarci il software.

Il file i2c.c è solo una prova.

In bocca al lupo!
