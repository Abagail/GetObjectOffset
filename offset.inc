#tryinclude <streamer>
#if !defined CreateDynamicObject
	#error "Streamer must be included."
#endif

#define OBJECT_EXTRA_TYPE_NONE          			(0)
#define OBJECT_EXTRA_TYPE_PLAYER          			(1)
#define OBJECT_EXTRA_TYPE_VEHICLE          		    (2)
#define OBJECT_EXTRA_TYPE_OBJECT          		    (3)
#define OBJECT_EXTRA_TYPE_DYNAMIC_OBJECT            (4)

static stock GetPosOffset(Float: p_p_x, Float: p_p_y, Float: p_p_z, Float: p_c_x, Float: p_c_y, Float: p_c_z, &Float:p_n_x, &Float:p_n_y, &Float: p_n_z)
{
	p_n_x = (p_p_x > p_c_x) ? (p_p_x - p_c_x) : (p_c_x - p_p_x);
	p_n_y = (p_p_y > p_c_y) ? (p_p_y - p_c_y) : (p_c_y - p_p_y);
	p_n_z = (p_p_z > p_c_z) ? (p_p_z - p_c_z) : (p_c_z - p_p_z);
	return true;
}

stock IsObjectInRangeOfPlayer(playerid, objectid, Float: radius)
{
	static Float: obj_r_x, Float: obj_r_y, Float: obj_r_z;
	GetObjectPos(objectid, obj_r_x, obj_r_y, obj_r_z);
	
	return IsPlayerInRangeOfPoint(playerid, radius, obj_r_x, obj_r_y, obj_r_z);
}

stock IsDynamicObjectInRangeOfPlayer(playerid, objectid, Float: radius)
{
	static Float: obj_r_x, Float: obj_r_y, Float: obj_r_z;
	GetDynamicObjectPos(objectid, obj_r_x, obj_r_y, obj_r_z);

	return IsPlayerInRangeOfPoint(playerid, radius, obj_r_x, obj_r_y, obj_r_z);
}

stock GetObjectOffset(objectid, bool: isdynamic, extratype, extraid, &Float: obj_off_ret_x, &Float: obj_off_ret_y, &Float: obj_off_ret_z)
{
	if(!isdynamic && !IsValidObject(objectid) || isdynamic & !IsValidDynamicObject(objectid))
	    return 0;
	    
	if(extratype <= OBJECT_EXTRA_TYPE_NONE || extratype > OBJECT_EXTRA_TYPE_DYNAMIC_OBJECT)
	    return 0;
	    
	static
	    Float: obj_off_comp_x,
	    Float: obj_off_comp_y,
	    Float: obj_off_comp_z,
	    
	    Float: obj_off_compto_x,
	    Float: obj_off_compto_y,
	    Float: obj_off_compto_z
	;
	
	switch(extratype)
	{
	    case OBJECT_EXTRA_TYPE_PLAYER:
	    {
			if(!IsPlayerConnected(extraid))
			    return 0;
			    
            GetObjectPos(objectid, obj_off_comp_x, obj_off_comp_y, obj_off_comp_z);
			GetPlayerPos(extraid, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z);
			
			return GetPosOffset(obj_off_comp_x, obj_off_comp_y, obj_off_comp_z, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z, obj_off_ret_x, obj_off_ret_y, obj_off_ret_z);
		}
		
		case OBJECT_EXTRA_TYPE_VEHICLE:
	    {
			if(!GetVehicleModel(extraid))
			    return 0;

            GetObjectPos(objectid, obj_off_comp_x, obj_off_comp_y, obj_off_comp_z);
			GetVehiclePos(extraid, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z);

			return GetPosOffset(obj_off_comp_x, obj_off_comp_y, obj_off_comp_z, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z, obj_off_ret_x, obj_off_ret_y, obj_off_ret_z);
		}
		
		case OBJECT_EXTRA_TYPE_OBJECT:
	    {
			if(!IsValidObject(extraid))
			    return 0;

            GetObjectPos(objectid, obj_off_comp_x, obj_off_comp_y, obj_off_comp_z);
			GetObjectPos(extraid, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z);

			return GetPosOffset(obj_off_comp_x, obj_off_comp_y, obj_off_comp_z, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z, obj_off_ret_x, obj_off_ret_y, obj_off_ret_z);
		}
		
		case OBJECT_EXTRA_TYPE_DYNAMIC_OBJECT:
	    {
			if(!IsValidDynamicObject(extraid))
			    return 0;

            GetObjectPos(objectid, obj_off_comp_x, obj_off_comp_y, obj_off_comp_z);
			GetDynamicObjectPos(extraid, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z);

			return GetPosOffset(obj_off_comp_x, obj_off_comp_y, obj_off_comp_z, obj_off_compto_x, obj_off_compto_y, obj_off_compto_z, obj_off_ret_x, obj_off_ret_y, obj_off_ret_z);
		}
	}
	
	return 0;
}