
#ifndef __mlgm_repository_h__
#define __mlgm_repository_h__

#include "mlgm_types.h"

typedef struct t_mlgm_repository
{

} mlgm_repository;

typedef struct t_mlgm_repo_access
{

    mlgm_string managerDomain;
    mlgm_string managerEmail;

    mlgm_string managedDomain;
    mlgm_string managedUserName;

    mlgm_string managedScene;
    mlgm_uint64 managedVersion;

    mlgm_string managedPassword;

} mlgm_repo_access;

#endif // __mlgm_repository_h__
