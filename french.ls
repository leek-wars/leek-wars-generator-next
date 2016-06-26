var french = function(n) {
	
	print(n)
	
	var	T = '-'
	var V = ''
	var x = String.split('s  un deux trois quatre cinq six sept huit neuf dix onze douze treize quatorze quinze seize dix vingt trente quarante cinquante soixante  quatre-vingt  cent', ' ')
	
	var b = n % 100
	var d = 17 + b / 10
	var u = n % 10
	var c = Number.floor(n / 100)
	var e = if (u - 1) then T else '-et-' end
	var L = Number.floor(Number.log10(n) / 3)
	var H = Number.pow(1000, L)
	var v = Number.floor(n / H)
	var i = [T, ' ', (if x[d] then 0 else d-- end) or (u += 10)][L > 1]
	
	return 
	if L < 1 then
		if c then
			(if c > 1 then french(c) + T else V end) + x[27] + x[c * !b < 2] 
			+ (if b then T else V end) + french(b) 
		else
			if n < 17 then
				x[n + 1] 
			else 
				if n < 20 then
					x[11] + T + x[u + 1] 
				else
					x[d] + (if u then e + french(u) else x[d != 25] end)
				end
			end
		end
	else 
		(if L * v > 1 then french(v) + i else V end) + 'mill' 
		+ [n %= H, 'e', 'ion', 'iard'][L] + x[v < 2 or L < 2] 
		+ (if n then i else V end) + french(n)
	end
}