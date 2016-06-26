
print("salut ! €")



let me = Fight.getEntity()
let him = me.getClosestEnemy()

print(him.name)
print(me.getChips())

me.moveToward(him, 999)

/*


let fortress = me.getChips()[0]

print(fortress)

let pistol = me.getWeapons()[0]

print(pistol)

if (Fight.getTurn() == 1) {

	//print("use chip fortress")
	//me.useChip(fortress, me)
	
	//me.setWeapon(pistol)
	
	me.say("Tayo!!")
}



//me.useWeapon(him)

/*
print("ldv: " + Map.lineOfSight(me.cell, him.cell))

print("ldv old: " + Map._lineOfSight(me.cell.id, him.cell.id))

print("distance: " + me.cell.distance(him.cell))

print("path length: " + Map.getPath(me.cell, him.cell).size())



/*

print("me : " + me.name)
print("him : " + him.name)

let chip = me.getChips()[0]
print(chip)

let res = me.useChip(chip, him)
print("useChip res: " + res)


let dist = me.cell.distance(him.cell)
print("distance : " + dist)

print("him : " + him.name)
print("my strength : " + me.getStrength())
print("his strength : " + him.strength)
print("his life : " + him.life)
print("his weapons: ")
print(him.getWeapons())

/*

let dist2 = Number.abs(me.cell.x - him.cell.x) + Number.abs(me.cell.y - him.cell.y)
print(dist2)


/*

"print(Entity.getWeapons(Fight.getEntity())[1].name) ; 
Entity.getWeapons(Fight.getEntity())[1].name = 'changed' ; ");



