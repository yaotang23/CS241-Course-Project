#include "usermap.h"

UserMap::UserMap()
{

}

void UserMap::paintUserMap(int user_id)
{
    for(int i=0;i<user.at(user_id).size();i++)
    {
        for(int j=i;j<user.at(user_id).size()-1;j++)
        {
            uint t1=user.at(user_id).at(j).dateTime.toTime_t();
            uint t2=user.at(user_id).at(j+1).dateTime.toTime_t();
            if(t1>t2)
            {
                cknode tmp=user.at(user_id)[j];
                user[user_id][j]=user[user_id][j+1];
                user[user_id][j+1]=tmp;

            }
        }
    }
    emit finish_user(user[user_id]);
}

void UserMap::paintLocMap(int loc_id)
{
    emit finish_loc(location[loc_id]);
}
