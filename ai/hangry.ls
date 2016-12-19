var me = Fight.getEntity()
var him = me.getClosestEnemy()

var weapon = me.getWeapons()[0]
System.print(weapon)

System.print(me.getWeapons())

me.say("Salut !")

me.setWeapon(weapon)

me.useWeapon(him)

me.moveToward(him, 5)
