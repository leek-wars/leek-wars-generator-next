let me = Fight.getEntity()

System.print(me)
System.print("I am " + me.name)
System.print("I am on cell " + me.cell.id)

let weapons = me.getWeapons()

System.print("My weapons : ")
System.print(weapons)
System.print(weapons ~~ x -> x.name)

let laser = me.getWeapons()[1]
System.print("My laser : ")
System.print(laser)

let enemy = me.getClosestEnemy()
System.print("My enemy : ")
System.print(enemy)

//System.print("Los between " + me.cell.id + ' and ' + enemy.cell.id + ' : ' + FightMap.lineOfSight(me.cell, enemy.cell))

System.print("Los old: " + FightMap._lineOfSight(me.cell.id, enemy.cell.id))

System.print("Distance: " + me.cell.distance(enemy.cell))

System.print("Path length: " + FightMap.getPath(me.cell, enemy.cell).size())

let dist2 = (me.cell.x - enemy.cell.x).abs() + (me.cell.y - enemy.cell.y).abs()
System.print("Handmade distance : " + dist2)
