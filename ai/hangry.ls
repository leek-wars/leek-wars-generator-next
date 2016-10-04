var me = Fight.getEntity()
var him = me.getClosestEnemy()

me.moveToward(him, 2)

me.useWeapon(him)
