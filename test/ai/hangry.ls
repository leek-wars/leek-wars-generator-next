var me = Fight.getEntity()
var him = me.getClosestEnemy()

var weapon = me.getWeapons()[0]
System.print(weapon)

var chip = me.getChips()[0]
System.print(chip)

System.print(me.getWeapons())

me.say("Salut !")

me.moveToward(him, 5)

me.setWeapon(weapon)

me.useWeapon(him)

me.moveToward(him, 5)

FightMap.cell(1, 1)
FightMap.lineOfSight(me.cell, him.cell)
FightMap.getPath(me.cell, him.cell)
