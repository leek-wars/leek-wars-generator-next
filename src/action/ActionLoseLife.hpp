package com.leekwars.game.fight.action;

import com.alibaba.fastjson.JSONArray;
import com.leekwars.game.fight.entity.Entity;

public class ActionLoseLife implements Action {

	private final int target;
	private final int pv;

	public ActionLoseLife(Entity target, int pv) {
		this.target = target.getFId();
		this.pv = pv;
	}

	@Override
	public JSONArray getJSON() {
		JSONArray retour = new JSONArray();
		retour.add(Action.LOST_LIFE);
		retour.add(target);
		retour.add(pv);
		return retour;
	}
}
