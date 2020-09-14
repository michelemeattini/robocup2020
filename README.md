# RoboCup 2020
 
Questa repository contiene il software più aggiornato sviluppato dal team _*Michele Meattini*_, Bilal Laasri, Mirko Soggetti, Pasquale de Roberto e Leonardo Crini per il robot *Mistake*.

In linea di massima funzionava ben sul robot cingolato. Il robot deve essere ben bilanciato per far si che questo codice funzioni bene. 
Se slitta e scivola in curva non è il software ma il robot non sbilanciato.

Il file Good Mistake.c è l'ultima bozza che abbiamo sviluppato, non è ottimizzata e si basa sulle funzioni che vengono importate dal file _function.h_.

La parte di raccogliere le palline nell'arena non è stata sviluppata per nulla.

La nostra idea era quella di utilizzare 2 Arduini e farli comunicare in seriale, di cui uno poi avremme comunicato tutto all'EV3.
Alla fine abbiamo abbandonato l'idea di utilizzarne due ed abbiamo deciso che sarebbe bastato un arduino solo ed al massimo un secondo solo per il giroscopio che alla fine non abbiamo utilizzato.
Lo schema elettrico non è aggiornato, se si vogliono utilizzare 22 arduini che comunicano in seriale una cosa importante è mettere degli switch tra tx rx dei due perchè altrimenti quando sono collegati non si può usare la seriale USB per caricarci il software.

Il file i2c.c è solo una prova.

In bocca al lupo!
