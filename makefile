poll_config: primaire secondaire trafic
	gcc poll_config.c -o poll_config
primaire:primaire.c
	gcc  primaire.c -o primaire
secondaire :secondaire.c
	gcc  secondaire.c -o secondaire
trafic :trafic.c
	gcc  trafic.c -o trafic
