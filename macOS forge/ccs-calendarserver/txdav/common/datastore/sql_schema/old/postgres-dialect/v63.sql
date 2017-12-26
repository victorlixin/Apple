-- -*- test-case-name: txdav.caldav.datastore.test.test_sql,txdav.carddav.datastore.test.test_sql -*-

----
-- Copyright (c) 2010-2017 Apple Inc. All rights reserved.
--
-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at
--
-- http://www.apache.org/licenses/LICENSE-2.0
--
-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.
----


-----------------
-- Resource ID --
-----------------

create sequence RESOURCE_ID_SEQ;


-- Unique named locks.  This table should always be empty, but rows are
-- temporarily created in order to prevent undesirable concurrency.
create table NAMED_LOCK (
    LOCK_NAME varchar(255) primary key
);


--------------------
-- Jobs           --
--------------------

create sequence JOB_SEQ;

create table JOB (
  JOB_ID      integer primary key default nextval('JOB_SEQ'), --implicit index
  WORK_TYPE   varchar(255) not null,
  PRIORITY    integer default 0,
  WEIGHT      integer default 0,
  NOT_BEFORE  timestamp not null,
  ASSIGNED    timestamp default null,
  OVERDUE     timestamp default null,
  FAILED      integer default 0,
  PAUSE       integer default 0
);

create index JOB_PRIORITY_ASSIGNED_PAUSE_NOT_BEFORE on
  JOB(PRIORITY, ASSIGNED, PAUSE, NOT_BEFORE);

create index JOB_ASSIGNED_PAUSE_NOT_BEFORE on
  JOB(ASSIGNED, PAUSE, NOT_BEFORE);

create index JOB_ASSIGNED_OVERDUE on
  JOB(ASSIGNED, OVERDUE);

-------------------
-- Calendar Home --
-------------------

create table CALENDAR_HOME (
  RESOURCE_ID      integer      primary key default nextval('RESOURCE_ID_SEQ'), -- implicit index
  OWNER_UID        varchar(255) not null,                		                -- implicit index
  STATUS           integer      default 0 not null,                             -- enum HOME_STATUS
  DATAVERSION      integer      default 0 not null,

  unique (OWNER_UID, STATUS)	-- implicit index
);

-- Enumeration of statuses

create table HOME_STATUS (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into HOME_STATUS values (0, 'normal' );
insert into HOME_STATUS values (1, 'external');
insert into HOME_STATUS values (2, 'purging');
insert into HOME_STATUS values (3, 'migrating');
insert into HOME_STATUS values (4, 'disabled');


--------------
-- Calendar --
--------------

create table CALENDAR (
  RESOURCE_ID integer   primary key default nextval('RESOURCE_ID_SEQ') -- implicit index
);


----------------------------
-- Calendar Home Metadata --
----------------------------

create table CALENDAR_HOME_METADATA (
  RESOURCE_ID              integer     primary key references CALENDAR_HOME on delete cascade, -- implicit index
  QUOTA_USED_BYTES         integer     default 0 not null,
  TRASH                    integer     default null references CALENDAR on delete set null,
  DEFAULT_EVENTS           integer     default null references CALENDAR on delete set null,
  DEFAULT_TASKS            integer     default null references CALENDAR on delete set null,
  DEFAULT_POLLS            integer     default null references CALENDAR on delete set null,
  ALARM_VEVENT_TIMED       text        default null,
  ALARM_VEVENT_ALLDAY      text        default null,
  ALARM_VTODO_TIMED        text        default null,
  ALARM_VTODO_ALLDAY       text        default null,
  AVAILABILITY             text        default null,
  CREATED                  timestamp   default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED                 timestamp   default timezone('UTC', CURRENT_TIMESTAMP)
);

create index CALENDAR_HOME_METADATA_TRASH on
  CALENDAR_HOME_METADATA(TRASH);
create index CALENDAR_HOME_METADATA_DEFAULT_EVENTS on
  CALENDAR_HOME_METADATA(DEFAULT_EVENTS);
create index CALENDAR_HOME_METADATA_DEFAULT_TASKS on
  CALENDAR_HOME_METADATA(DEFAULT_TASKS);
create index CALENDAR_HOME_METADATA_DEFAULT_POLLS on
  CALENDAR_HOME_METADATA(DEFAULT_POLLS);


-----------------------
-- Calendar Metadata --
-----------------------

create table CALENDAR_METADATA (
  RESOURCE_ID           integer      primary key references CALENDAR on delete cascade, -- implicit index
  SUPPORTED_COMPONENTS  varchar(255) default null,
  CHILD_TYPE            integer      default 0 not null,                             	-- enum CHILD_TYPE
  TRASHED               timestamp    default null,
  IS_IN_TRASH           boolean      default false not null, -- collection is in the trash
  CREATED               timestamp    default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED              timestamp    default timezone('UTC', CURRENT_TIMESTAMP)
);

-- Enumeration of child type

create table CHILD_TYPE (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into CHILD_TYPE values (0, 'normal');
insert into CHILD_TYPE values (1, 'inbox');
insert into CHILD_TYPE values (2, 'trash');


------------------------
-- Calendar Migration --
------------------------

create table CALENDAR_MIGRATION (
  CALENDAR_HOME_RESOURCE_ID		integer references CALENDAR_HOME on delete cascade,
  REMOTE_RESOURCE_ID			integer not null,
  LOCAL_RESOURCE_ID				integer	references CALENDAR on delete cascade,
  LAST_SYNC_TOKEN				varchar(255),

  primary key (CALENDAR_HOME_RESOURCE_ID, REMOTE_RESOURCE_ID) -- implicit index
);

create index CALENDAR_MIGRATION_LOCAL_RESOURCE_ID on
  CALENDAR_MIGRATION(LOCAL_RESOURCE_ID);


---------------------------
-- Sharing Notifications --
---------------------------

create table NOTIFICATION_HOME (
  RESOURCE_ID integer      primary key default nextval('RESOURCE_ID_SEQ'), -- implicit index
  OWNER_UID   varchar(255) not null,	                                   -- implicit index
  STATUS      integer      default 0 not null,                             -- enum HOME_STATUS
  DATAVERSION integer      default 0 not null,

  unique (OWNER_UID, STATUS)	-- implicit index
);

create table NOTIFICATION (
  RESOURCE_ID                   integer      primary key default nextval('RESOURCE_ID_SEQ'), -- implicit index
  NOTIFICATION_HOME_RESOURCE_ID integer      not null references NOTIFICATION_HOME,
  NOTIFICATION_UID              varchar(255) not null,
  NOTIFICATION_TYPE             varchar(255) not null,
  NOTIFICATION_DATA             text         not null,
  MD5                           char(32)     not null,
  CREATED                       timestamp    default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED                      timestamp    default timezone('UTC', CURRENT_TIMESTAMP),

  unique (NOTIFICATION_UID, NOTIFICATION_HOME_RESOURCE_ID) -- implicit index
);

create index NOTIFICATION_NOTIFICATION_HOME_RESOURCE_ID on
  NOTIFICATION(NOTIFICATION_HOME_RESOURCE_ID);


-------------------
-- Calendar Bind --
-------------------

-- Joins CALENDAR_HOME and CALENDAR

create table CALENDAR_BIND (
  CALENDAR_HOME_RESOURCE_ID integer      not null references CALENDAR_HOME,
  CALENDAR_RESOURCE_ID      integer      not null references CALENDAR on delete cascade,
  CALENDAR_RESOURCE_NAME    varchar(255) not null,
  BIND_MODE                 integer      not null, -- enum CALENDAR_BIND_MODE
  BIND_STATUS               integer      not null, -- enum CALENDAR_BIND_STATUS
  BIND_REVISION             integer      default 0 not null,
  BIND_UID                  varchar(36)  default null,
  MESSAGE                   text,
  TRANSP                    integer      default 0 not null, -- enum CALENDAR_TRANSP
  ALARM_VEVENT_TIMED        text         default null,
  ALARM_VEVENT_ALLDAY       text         default null,
  ALARM_VTODO_TIMED         text         default null,
  ALARM_VTODO_ALLDAY        text         default null,
  TIMEZONE                  text         default null,

  primary key (CALENDAR_HOME_RESOURCE_ID, CALENDAR_RESOURCE_ID), -- implicit index
  unique (CALENDAR_HOME_RESOURCE_ID, CALENDAR_RESOURCE_NAME)     -- implicit index
);

create index CALENDAR_BIND_RESOURCE_ID on
  CALENDAR_BIND(CALENDAR_RESOURCE_ID);

-- Enumeration of calendar bind modes

create table CALENDAR_BIND_MODE (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into CALENDAR_BIND_MODE values (0, 'own'  );
insert into CALENDAR_BIND_MODE values (1, 'read' );
insert into CALENDAR_BIND_MODE values (2, 'write');
insert into CALENDAR_BIND_MODE values (3, 'direct');
insert into CALENDAR_BIND_MODE values (4, 'indirect');
insert into CALENDAR_BIND_MODE values (5, 'group');
insert into CALENDAR_BIND_MODE values (6, 'group_read');
insert into CALENDAR_BIND_MODE values (7, 'group_write');

-- Enumeration of statuses

create table CALENDAR_BIND_STATUS (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into CALENDAR_BIND_STATUS values (0, 'invited' );
insert into CALENDAR_BIND_STATUS values (1, 'accepted');
insert into CALENDAR_BIND_STATUS values (2, 'declined');
insert into CALENDAR_BIND_STATUS values (3, 'invalid');
insert into CALENDAR_BIND_STATUS values (4, 'deleted');


-- Enumeration of transparency

create table CALENDAR_TRANSP (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into CALENDAR_TRANSP values (0, 'opaque' );
insert into CALENDAR_TRANSP values (1, 'transparent');


---------------------
-- Calendar Object --
---------------------

create table CALENDAR_OBJECT (
  RESOURCE_ID          integer      primary key default nextval('RESOURCE_ID_SEQ'), -- implicit index
  CALENDAR_RESOURCE_ID integer      not null references CALENDAR on delete cascade,
  RESOURCE_NAME        varchar(255) not null,
  ICALENDAR_TEXT       text         not null,
  ICALENDAR_UID        varchar(255) not null,
  ICALENDAR_TYPE       varchar(255) not null,
  ATTACHMENTS_MODE     integer      default 0 not null, -- enum CALENDAR_OBJ_ATTACHMENTS_MODE
  DROPBOX_ID           varchar(255),
  ORGANIZER            varchar(255),
  RECURRANCE_MIN       date,        -- minimum date that recurrences have been expanded to.
  RECURRANCE_MAX       date,        -- maximum date that recurrences have been expanded to.
  ACCESS               integer      default 0 not null,
  SCHEDULE_OBJECT      boolean      default false,
  SCHEDULE_TAG         varchar(36)  default null,
  SCHEDULE_ETAGS       text         default null,
  PRIVATE_COMMENTS     boolean      default false not null,
  MD5                  char(32)     not null,
  TRASHED              timestamp    default null,
  ORIGINAL_COLLECTION  integer      default null, -- calendar_resource_id prior to trash
  CREATED              timestamp    default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED             timestamp    default timezone('UTC', CURRENT_TIMESTAMP),
  DATAVERSION          integer      default 0 not null,

  unique (CALENDAR_RESOURCE_ID, RESOURCE_NAME) -- implicit index

  -- since the 'inbox' is a 'calendar resource' for the purpose of storing
  -- calendar objects, this constraint has to be selectively enforced by the
  -- application layer.

  -- unique (CALENDAR_RESOURCE_ID, ICALENDAR_UID)
);

create index CALENDAR_OBJECT_CALENDAR_RESOURCE_ID_AND_ICALENDAR_UID on
  CALENDAR_OBJECT(CALENDAR_RESOURCE_ID, ICALENDAR_UID);

create index CALENDAR_OBJECT_CALENDAR_RESOURCE_ID_RECURRANCE_MAX_MIN on
  CALENDAR_OBJECT(CALENDAR_RESOURCE_ID, RECURRANCE_MAX, RECURRANCE_MIN);

create index CALENDAR_OBJECT_ICALENDAR_UID on
  CALENDAR_OBJECT(ICALENDAR_UID);

create index CALENDAR_OBJECT_DROPBOX_ID on
  CALENDAR_OBJECT(DROPBOX_ID);

create index CALENDAR_OBJECT_ORIGINAL_COLLECTION_AND_TRASHED on
  CALENDAR_OBJECT(ORIGINAL_COLLECTION, TRASHED);

-- Enumeration of attachment modes

create table CALENDAR_OBJ_ATTACHMENTS_MODE (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into CALENDAR_OBJ_ATTACHMENTS_MODE values (0, 'none' );
insert into CALENDAR_OBJ_ATTACHMENTS_MODE values (1, 'read' );
insert into CALENDAR_OBJ_ATTACHMENTS_MODE values (2, 'write');


-- Enumeration of calendar access types

create table CALENDAR_ACCESS_TYPE (
  ID          integer     primary key,
  DESCRIPTION varchar(32) not null unique
);

insert into CALENDAR_ACCESS_TYPE values (0, ''             );
insert into CALENDAR_ACCESS_TYPE values (1, 'public'       );
insert into CALENDAR_ACCESS_TYPE values (2, 'private'      );
insert into CALENDAR_ACCESS_TYPE values (3, 'confidential' );
insert into CALENDAR_ACCESS_TYPE values (4, 'restricted'   );


-----------------
-- Instance ID --
-----------------

create sequence INSTANCE_ID_SEQ;


----------------
-- Time Range --
----------------

create table TIME_RANGE (
  INSTANCE_ID                 integer        primary key default nextval('INSTANCE_ID_SEQ'), -- implicit index
  CALENDAR_RESOURCE_ID        integer        not null references CALENDAR on delete cascade,
  CALENDAR_OBJECT_RESOURCE_ID integer        not null references CALENDAR_OBJECT on delete cascade,
  FLOATING                    boolean        not null,
  START_DATE                  timestamp      not null,
  END_DATE                    timestamp      not null,
  FBTYPE                      integer        not null,
  TRANSPARENT                 boolean        not null
);

create index TIME_RANGE_CALENDAR_RESOURCE_ID on
  TIME_RANGE(CALENDAR_RESOURCE_ID);
create index TIME_RANGE_CALENDAR_OBJECT_RESOURCE_ID on
  TIME_RANGE(CALENDAR_OBJECT_RESOURCE_ID);


-- Enumeration of free/busy types

create table FREE_BUSY_TYPE (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into FREE_BUSY_TYPE values (0, 'unknown'         );
insert into FREE_BUSY_TYPE values (1, 'free'            );
insert into FREE_BUSY_TYPE values (2, 'busy'            );
insert into FREE_BUSY_TYPE values (3, 'busy-unavailable');
insert into FREE_BUSY_TYPE values (4, 'busy-tentative'  );


-------------------
-- Per-user data --
-------------------

create table PERUSER (
  TIME_RANGE_INSTANCE_ID      integer      not null references TIME_RANGE on delete cascade,
  USER_ID                     varchar(255) not null,
  TRANSPARENT                 boolean      not null,
  ADJUSTED_START_DATE         timestamp    default null,
  ADJUSTED_END_DATE           timestamp    default null,

  primary key (TIME_RANGE_INSTANCE_ID, USER_ID)    -- implicit index
);


-------------------------------
-- Calendar Object Migration --
-------------------------------

create table CALENDAR_OBJECT_MIGRATION (
  CALENDAR_HOME_RESOURCE_ID		integer references CALENDAR_HOME on delete cascade,
  REMOTE_RESOURCE_ID			integer not null,
  LOCAL_RESOURCE_ID				integer	references CALENDAR_OBJECT on delete cascade,

  primary key (CALENDAR_HOME_RESOURCE_ID, REMOTE_RESOURCE_ID) -- implicit index
);

create index CALENDAR_OBJECT_MIGRATION_HOME_LOCAL on
  CALENDAR_OBJECT_MIGRATION(CALENDAR_HOME_RESOURCE_ID, LOCAL_RESOURCE_ID);
create index CALENDAR_OBJECT_MIGRATION_LOCAL_RESOURCE_ID on
  CALENDAR_OBJECT_MIGRATION(LOCAL_RESOURCE_ID);


----------------
-- Attachment --
----------------

create sequence ATTACHMENT_ID_SEQ;

create table ATTACHMENT (
  ATTACHMENT_ID               integer           primary key default nextval('ATTACHMENT_ID_SEQ'), -- implicit index
  CALENDAR_HOME_RESOURCE_ID   integer           not null references CALENDAR_HOME,
  DROPBOX_ID                  varchar(255),
  CONTENT_TYPE                varchar(255)      not null,
  SIZE                        integer           not null,
  MD5                         char(32)          not null,
  CREATED                     timestamp default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED                    timestamp default timezone('UTC', CURRENT_TIMESTAMP),
  PATH                        varchar(1024)     not null
);

create index ATTACHMENT_CALENDAR_HOME_RESOURCE_ID on
  ATTACHMENT(CALENDAR_HOME_RESOURCE_ID);

create index ATTACHMENT_DROPBOX_ID on
  ATTACHMENT(DROPBOX_ID);

-- Many-to-many relationship between attachments and calendar objects
create table ATTACHMENT_CALENDAR_OBJECT (
  ATTACHMENT_ID                  integer      not null references ATTACHMENT on delete cascade,
  MANAGED_ID                     varchar(255) not null,
  CALENDAR_OBJECT_RESOURCE_ID    integer      not null references CALENDAR_OBJECT on delete cascade,

  primary key (ATTACHMENT_ID, CALENDAR_OBJECT_RESOURCE_ID), -- implicit index
  unique (MANAGED_ID, CALENDAR_OBJECT_RESOURCE_ID) --implicit index
);

create index ATTACHMENT_CALENDAR_OBJECT_CALENDAR_OBJECT_RESOURCE_ID on
  ATTACHMENT_CALENDAR_OBJECT(CALENDAR_OBJECT_RESOURCE_ID);

-----------------------------------
-- Calendar Attachment Migration --
-----------------------------------

create table ATTACHMENT_MIGRATION (
  CALENDAR_HOME_RESOURCE_ID		integer references CALENDAR_HOME on delete cascade,
  REMOTE_RESOURCE_ID			integer not null,
  LOCAL_RESOURCE_ID				integer	references ATTACHMENT on delete cascade,

  primary key (CALENDAR_HOME_RESOURCE_ID, REMOTE_RESOURCE_ID) -- implicit index
);

create index ATTACHMENT_MIGRATION_HOME_LOCAL on
  ATTACHMENT_MIGRATION(CALENDAR_HOME_RESOURCE_ID, LOCAL_RESOURCE_ID);
create index ATTACHMENT_MIGRATION_LOCAL_RESOURCE_ID on
  ATTACHMENT_MIGRATION(LOCAL_RESOURCE_ID);


-----------------------
-- Resource Property --
-----------------------

create table RESOURCE_PROPERTY (
  RESOURCE_ID integer      not null, -- foreign key: *.RESOURCE_ID
  NAME        varchar(255) not null,
  VALUE       text         not null, -- FIXME: xml?
  VIEWER_UID  varchar(255),

  primary key (RESOURCE_ID, NAME, VIEWER_UID) -- implicit index
);


----------------------
-- AddressBook Home --
----------------------

create table ADDRESSBOOK_HOME (
  RESOURCE_ID                   integer         primary key default nextval('RESOURCE_ID_SEQ'), -- implicit index
  ADDRESSBOOK_PROPERTY_STORE_ID integer         default nextval('RESOURCE_ID_SEQ') not null,    -- implicit index
  OWNER_UID                     varchar(255)    not null,
  STATUS                        integer         default 0 not null,                             -- enum HOME_STATUS
  DATAVERSION                   integer         default 0 not null,

  unique (OWNER_UID, STATUS)	-- implicit index
);


-------------------------------
-- AddressBook Home Metadata --
-------------------------------

create table ADDRESSBOOK_HOME_METADATA (
  RESOURCE_ID      integer      primary key references ADDRESSBOOK_HOME on delete cascade, -- implicit index
  QUOTA_USED_BYTES integer      default 0 not null,
  CREATED          timestamp    default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED         timestamp    default timezone('UTC', CURRENT_TIMESTAMP)
);


-----------------------------
-- Shared AddressBook Bind --
-----------------------------

-- Joins sharee ADDRESSBOOK_HOME and owner ADDRESSBOOK_HOME

create table SHARED_ADDRESSBOOK_BIND (
  ADDRESSBOOK_HOME_RESOURCE_ID          integer         not null references ADDRESSBOOK_HOME,
  OWNER_HOME_RESOURCE_ID                integer         not null references ADDRESSBOOK_HOME on delete cascade,
  ADDRESSBOOK_RESOURCE_NAME             varchar(255)    not null,
  BIND_MODE                             integer         not null, -- enum CALENDAR_BIND_MODE
  BIND_STATUS                           integer         not null, -- enum CALENDAR_BIND_STATUS
  BIND_REVISION                         integer         default 0 not null,
  BIND_UID                              varchar(36)     default null,
  MESSAGE                               text,                     -- FIXME: xml?

  primary key (ADDRESSBOOK_HOME_RESOURCE_ID, OWNER_HOME_RESOURCE_ID), -- implicit index
  unique (ADDRESSBOOK_HOME_RESOURCE_ID, ADDRESSBOOK_RESOURCE_NAME)     -- implicit index
);

create index SHARED_ADDRESSBOOK_BIND_RESOURCE_ID on
  SHARED_ADDRESSBOOK_BIND(OWNER_HOME_RESOURCE_ID);


------------------------
-- AddressBook Object --
------------------------

create table ADDRESSBOOK_OBJECT (
  RESOURCE_ID                   integer         primary key default nextval('RESOURCE_ID_SEQ'),    -- implicit index
  ADDRESSBOOK_HOME_RESOURCE_ID  integer         not null references ADDRESSBOOK_HOME on delete cascade,
  RESOURCE_NAME                 varchar(255)    not null,
  VCARD_TEXT                    text            not null,
  VCARD_UID                     varchar(255)    not null,
  KIND                          integer         not null,  -- enum ADDRESSBOOK_OBJECT_KIND
  MD5                           char(32)        not null,
  TRASHED                       timestamp       default null,
  IS_IN_TRASH                   boolean         default false not null,
  CREATED                       timestamp       default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED                      timestamp       default timezone('UTC', CURRENT_TIMESTAMP),
  DATAVERSION                   integer         default 0 not null,

  unique (ADDRESSBOOK_HOME_RESOURCE_ID, RESOURCE_NAME), -- implicit index
  unique (ADDRESSBOOK_HOME_RESOURCE_ID, VCARD_UID)      -- implicit index
);


-----------------------------
-- AddressBook Object kind --
-----------------------------

create table ADDRESSBOOK_OBJECT_KIND (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into ADDRESSBOOK_OBJECT_KIND values (0, 'person');
insert into ADDRESSBOOK_OBJECT_KIND values (1, 'group' );
insert into ADDRESSBOOK_OBJECT_KIND values (2, 'resource');
insert into ADDRESSBOOK_OBJECT_KIND values (3, 'location');


----------------------------------
-- Revisions, forward reference --
----------------------------------

create sequence REVISION_SEQ;

---------------------------------
-- Address Book Object Members --
---------------------------------

create table ABO_MEMBERS (
  GROUP_ID        integer     not null, -- references ADDRESSBOOK_OBJECT on delete cascade,   -- AddressBook Object's (kind=='group') RESOURCE_ID
  ADDRESSBOOK_ID  integer     not null references ADDRESSBOOK_HOME on delete cascade,
  MEMBER_ID       integer     not null, -- references ADDRESSBOOK_OBJECT,                     -- member AddressBook Object's RESOURCE_ID
  REVISION        integer     default nextval('REVISION_SEQ') not null,
  REMOVED         boolean     default false not null,
  MODIFIED        timestamp   default timezone('UTC', CURRENT_TIMESTAMP),

  primary key (GROUP_ID, MEMBER_ID, REVISION) -- implicit index
);

create index ABO_MEMBERS_ADDRESSBOOK_ID on
  ABO_MEMBERS(ADDRESSBOOK_ID);
create index ABO_MEMBERS_MEMBER_ID on
  ABO_MEMBERS(MEMBER_ID);

------------------------------------------
-- Address Book Object Foreign Members  --
------------------------------------------

create table ABO_FOREIGN_MEMBERS (
  GROUP_ID           integer      not null references ADDRESSBOOK_OBJECT on delete cascade,  -- AddressBook Object's (kind=='group') RESOURCE_ID
  ADDRESSBOOK_ID     integer      not null references ADDRESSBOOK_HOME on delete cascade,
  MEMBER_ADDRESS     varchar(255) not null,                                                  -- member AddressBook Object's 'calendar' address

  primary key (GROUP_ID, MEMBER_ADDRESS) -- implicit index
);

create index ABO_FOREIGN_MEMBERS_ADDRESSBOOK_ID on
  ABO_FOREIGN_MEMBERS(ADDRESSBOOK_ID);

-----------------------
-- Shared Group Bind --
-----------------------

-- Joins ADDRESSBOOK_HOME and ADDRESSBOOK_OBJECT (kind == group)

create table SHARED_GROUP_BIND (
  ADDRESSBOOK_HOME_RESOURCE_ID      integer      not null references ADDRESSBOOK_HOME,
  GROUP_RESOURCE_ID                 integer      not null references ADDRESSBOOK_OBJECT on delete cascade,
  GROUP_ADDRESSBOOK_NAME            varchar(255) not null,
  BIND_MODE                         integer      not null, -- enum CALENDAR_BIND_MODE
  BIND_STATUS                       integer      not null, -- enum CALENDAR_BIND_STATUS
  BIND_REVISION                     integer      default 0 not null,
  BIND_UID                          varchar(36)  default null,
  MESSAGE                           text,                  -- FIXME: xml?

  primary key (ADDRESSBOOK_HOME_RESOURCE_ID, GROUP_RESOURCE_ID), -- implicit index
  unique (ADDRESSBOOK_HOME_RESOURCE_ID, GROUP_ADDRESSBOOK_NAME)  -- implicit index
);

create index SHARED_GROUP_BIND_RESOURCE_ID on
  SHARED_GROUP_BIND(GROUP_RESOURCE_ID);


---------------
-- Revisions --
---------------

-- create sequence REVISION_SEQ;


-------------------------------
-- Calendar Object Revisions --
-------------------------------

create table CALENDAR_OBJECT_REVISIONS (
  CALENDAR_HOME_RESOURCE_ID integer      not null references CALENDAR_HOME,
  CALENDAR_RESOURCE_ID      integer      references CALENDAR,
  CALENDAR_NAME             varchar(255) default null,
  RESOURCE_NAME             varchar(255),
  REVISION                  integer      default nextval('REVISION_SEQ') not null,
  DELETED                   boolean      not null,
  MODIFIED                  timestamp    default timezone('UTC', CURRENT_TIMESTAMP) not null,

  unique (CALENDAR_HOME_RESOURCE_ID, CALENDAR_RESOURCE_ID, CALENDAR_NAME, RESOURCE_NAME)    -- implicit index
);

create index CALENDAR_OBJECT_REVISIONS_RESOURCE_ID_RESOURCE_NAME_DELETED_REVISION
  on CALENDAR_OBJECT_REVISIONS(CALENDAR_RESOURCE_ID, RESOURCE_NAME, DELETED, REVISION);

create index CALENDAR_OBJECT_REVISIONS_RESOURCE_ID_REVISION
  on CALENDAR_OBJECT_REVISIONS(CALENDAR_RESOURCE_ID, REVISION);

create index CALENDAR_OBJECT_REVISIONS_HOME_RESOURCE_ID_REVISION
  on CALENDAR_OBJECT_REVISIONS(CALENDAR_HOME_RESOURCE_ID, REVISION);

create index CALENDAR_OBJECT_REVISIONS_REVISION
  on CALENDAR_OBJECT_REVISIONS(REVISION);


----------------------------------
-- AddressBook Object Revisions --
----------------------------------

create table ADDRESSBOOK_OBJECT_REVISIONS (
  ADDRESSBOOK_HOME_RESOURCE_ID  integer      not null references ADDRESSBOOK_HOME,
  OWNER_HOME_RESOURCE_ID        integer      references ADDRESSBOOK_HOME,
  ADDRESSBOOK_NAME              varchar(255) default null,
  OBJECT_RESOURCE_ID            integer      default 0,
  RESOURCE_NAME                 varchar(255),
  REVISION                      integer      default nextval('REVISION_SEQ') not null,
  DELETED                       boolean      not null,
  MODIFIED                      timestamp    default timezone('UTC', CURRENT_TIMESTAMP) not null,

  unique (ADDRESSBOOK_HOME_RESOURCE_ID, OWNER_HOME_RESOURCE_ID, ADDRESSBOOK_NAME, RESOURCE_NAME)    -- implicit index
);

create index ADDRESSBOOK_OBJECT_REVISIONS_OWNER_HOME_RESOURCE_ID_RESOURCE_NAME_DELETED_REVISION
  on ADDRESSBOOK_OBJECT_REVISIONS(OWNER_HOME_RESOURCE_ID, RESOURCE_NAME, DELETED, REVISION);

create index ADDRESSBOOK_OBJECT_REVISIONS_OWNER_HOME_RESOURCE_ID_REVISION
  on ADDRESSBOOK_OBJECT_REVISIONS(OWNER_HOME_RESOURCE_ID, REVISION);

create index ADDRESSBOOK_OBJECT_REVISIONS_REVISION
  on ADDRESSBOOK_OBJECT_REVISIONS(REVISION);


-----------------------------------
-- Notification Object Revisions --
-----------------------------------

create table NOTIFICATION_OBJECT_REVISIONS (
  NOTIFICATION_HOME_RESOURCE_ID integer      not null references NOTIFICATION_HOME on delete cascade,
  RESOURCE_NAME                 varchar(255),
  REVISION                      integer      default nextval('REVISION_SEQ') not null,
  DELETED                       boolean      not null,
  MODIFIED                      timestamp    default timezone('UTC', CURRENT_TIMESTAMP) not null,

  unique (NOTIFICATION_HOME_RESOURCE_ID, RESOURCE_NAME) -- implicit index
);

create index NOTIFICATION_OBJECT_REVISIONS_RESOURCE_ID_REVISION
  on NOTIFICATION_OBJECT_REVISIONS(NOTIFICATION_HOME_RESOURCE_ID, REVISION);

create index NOTIFICATION_OBJECT_REVISIONS_REVISION
  on NOTIFICATION_OBJECT_REVISIONS(REVISION);


-------------------------------------------
-- Apple Push Notification Subscriptions --
-------------------------------------------

create table APN_SUBSCRIPTIONS (
  TOKEN                         varchar(255) not null,
  RESOURCE_KEY                  varchar(255) not null,
  MODIFIED                      integer      not null,
  SUBSCRIBER_GUID               varchar(255) not null,
  USER_AGENT                    varchar(255) default null,
  IP_ADDR                       varchar(255) default null,

  primary key (TOKEN, RESOURCE_KEY) -- implicit index
);

create index APN_SUBSCRIPTIONS_RESOURCE_KEY
  on APN_SUBSCRIPTIONS(RESOURCE_KEY);

create index APN_SUBSCRIPTIONS_MODIFIED
  on APN_SUBSCRIPTIONS(MODIFIED);

-----------------
-- IMIP Tokens --
-----------------

create table IMIP_TOKENS (
  TOKEN                         varchar(255) not null,
  ORGANIZER                     varchar(255) not null,
  ATTENDEE                      varchar(255) not null,
  ICALUID                       varchar(255) not null,
  ACCESSED                      timestamp    default timezone('UTC', CURRENT_TIMESTAMP),

  primary key (ORGANIZER, ATTENDEE, ICALUID) -- implicit index
);

create index IMIP_TOKENS_TOKEN
  on IMIP_TOKENS(TOKEN);


----------------
-- Work Items --
----------------

create sequence WORKITEM_SEQ;

---------------
-- Test Work --
---------------

create table TEST_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  DELAY 						integer
);

create index TEST_WORK_JOB_ID on
  TEST_WORK(JOB_ID);

-------------------------------------
-- Apple Push Notification Purging --
-------------------------------------

create table APN_PURGING_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index APN_PURGING_WORK_JOB_ID on
  APN_PURGING_WORK(JOB_ID);


---------------------------
-- IMIP Inivitation Work --
---------------------------

create table IMIP_INVITATION_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  FROM_ADDR                     varchar(255) not null,
  TO_ADDR                       varchar(255) not null,
  ICALENDAR_TEXT                text         not null
);

create index IMIP_INVITATION_WORK_JOB_ID on
  IMIP_INVITATION_WORK(JOB_ID);

-----------------------
-- IMIP Polling Work --
-----------------------

create table IMIP_POLLING_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index IMIP_POLLING_WORK_JOB_ID on
  IMIP_POLLING_WORK(JOB_ID);


---------------------
-- IMIP Reply Work --
---------------------

create table IMIP_REPLY_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  ORGANIZER                     varchar(255) not null,
  ATTENDEE                      varchar(255) not null,
  ICALENDAR_TEXT                text         not null
);

create index IMIP_REPLY_WORK_JOB_ID on
  IMIP_REPLY_WORK(JOB_ID);


------------------------
-- Push Notifications --
------------------------

create table PUSH_NOTIFICATION_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  PUSH_ID                       varchar(255) not null,
  PUSH_PRIORITY                 integer      not null -- 1:low 5:medium 10:high
);

create index PUSH_NOTIFICATION_WORK_JOB_ID on
  PUSH_NOTIFICATION_WORK(JOB_ID);
create index PUSH_NOTIFICATION_WORK_PUSH_ID on
  PUSH_NOTIFICATION_WORK(PUSH_ID);

-----------------
-- GroupCacher --
-----------------

create table GROUP_CACHER_POLLING_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index GROUP_CACHER_POLLING_WORK_JOB_ID on
  GROUP_CACHER_POLLING_WORK(JOB_ID);

create table GROUP_REFRESH_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  GROUP_UID                     varchar(255) not null
);

create index GROUP_REFRESH_WORK_JOB_ID on
  GROUP_REFRESH_WORK(JOB_ID);
create index GROUP_REFRESH_WORK_GROUP_UID on
  GROUP_REFRESH_WORK(GROUP_UID);

create table GROUP_DELEGATE_CHANGES_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  DELEGATOR_UID                 varchar(255) not null,
  READ_DELEGATE_UID             varchar(255) not null,
  WRITE_DELEGATE_UID            varchar(255) not null
);

create index GROUP_DELEGATE_CHANGES_WORK_JOB_ID on
  GROUP_DELEGATE_CHANGES_WORK(JOB_ID);
create index GROUP_DELEGATE_CHANGES_WORK_DELEGATOR_UID on
  GROUP_DELEGATE_CHANGES_WORK(DELEGATOR_UID);

create table GROUPS (
  GROUP_ID                      integer      primary key default nextval('RESOURCE_ID_SEQ'),    -- implicit index
  NAME                          varchar(255) not null,
  GROUP_UID                     varchar(255) not null unique,									-- implicit index
  MEMBERSHIP_HASH               varchar(255) not null,
  EXTANT                        integer default 1,
  CREATED                       timestamp default timezone('UTC', CURRENT_TIMESTAMP),
  MODIFIED                      timestamp default timezone('UTC', CURRENT_TIMESTAMP)
);

create table GROUP_MEMBERSHIP (
  GROUP_ID                     integer not null references GROUPS on delete cascade,
  MEMBER_UID                   varchar(255) not null,

  primary key (GROUP_ID, MEMBER_UID)
);

create index GROUP_MEMBERSHIP_MEMBER on
  GROUP_MEMBERSHIP(MEMBER_UID);

create table GROUP_ATTENDEE_RECONCILE_WORK (
  WORK_ID                       integer primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer not null references JOB,
  RESOURCE_ID                   integer not null references CALENDAR_OBJECT on delete cascade,
  GROUP_ID                      integer not null references GROUPS on delete cascade
);

create index GROUP_ATTENDEE_RECONCILE_WORK_JOB_ID on
  GROUP_ATTENDEE_RECONCILE_WORK(JOB_ID);
create index GROUP_ATTENDEE_RECONCILE_WORK_RESOURCE_ID on
  GROUP_ATTENDEE_RECONCILE_WORK(RESOURCE_ID);
create index GROUP_ATTENDEE_RECONCILE_WORK_GROUP_ID on
  GROUP_ATTENDEE_RECONCILE_WORK(GROUP_ID);


create table GROUP_ATTENDEE (
  GROUP_ID                      integer not null references GROUPS on delete cascade,
  RESOURCE_ID                   integer not null references CALENDAR_OBJECT on delete cascade,
  MEMBERSHIP_HASH               varchar(255) not null,

  primary key (GROUP_ID, RESOURCE_ID)
);

create index GROUP_ATTENDEE_RESOURCE_ID on
  GROUP_ATTENDEE(RESOURCE_ID);


create table GROUP_SHAREE_RECONCILE_WORK (
  WORK_ID                       integer primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer not null references JOB,
  CALENDAR_ID                   integer	not null references CALENDAR on delete cascade,
  GROUP_ID                      integer not null references GROUPS on delete cascade
);

create index GROUP_SHAREE_RECONCILE_WORK_JOB_ID on
  GROUP_SHAREE_RECONCILE_WORK(JOB_ID);
create index GROUP_SHAREE_RECONCILE_WORK_CALENDAR_ID on
  GROUP_SHAREE_RECONCILE_WORK(CALENDAR_ID);
create index GROUP_SHAREE_RECONCILE_WORK_GROUP_ID on
  GROUP_SHAREE_RECONCILE_WORK(GROUP_ID);


create table GROUP_SHAREE (
  GROUP_ID                      integer not null references GROUPS on delete cascade,
  CALENDAR_ID      				integer not null references CALENDAR on delete cascade,
  GROUP_BIND_MODE               integer not null, -- enum CALENDAR_BIND_MODE
  MEMBERSHIP_HASH               varchar(255) not null,

  primary key (GROUP_ID, CALENDAR_ID)
);

create index GROUP_SHAREE_CALENDAR_ID on
  GROUP_SHAREE(CALENDAR_ID);

---------------
-- Delegates --
---------------

create table DELEGATES (
  DELEGATOR                     varchar(255) not null,
  DELEGATE                      varchar(255) not null,
  READ_WRITE                    integer      not null, -- 1 = ReadWrite, 0 = ReadOnly

  primary key (DELEGATOR, READ_WRITE, DELEGATE)
);
create index DELEGATE_TO_DELEGATOR on
  DELEGATES(DELEGATE, READ_WRITE, DELEGATOR);

create table DELEGATE_GROUPS (
  DELEGATOR                     varchar(255) not null,
  GROUP_ID                      integer      not null references GROUPS on delete cascade,
  READ_WRITE                    integer      not null, -- 1 = ReadWrite, 0 = ReadOnly
  IS_EXTERNAL                   integer      not null, -- 1 = External, 0 = Internal

  primary key (DELEGATOR, READ_WRITE, GROUP_ID)
);
create index DELEGATE_GROUPS_GROUP_ID on
  DELEGATE_GROUPS(GROUP_ID);

create table EXTERNAL_DELEGATE_GROUPS (
  DELEGATOR                     varchar(255) primary key,
  GROUP_UID_READ                varchar(255),
  GROUP_UID_WRITE               varchar(255)
);

--------------------------
-- Object Splitter Work --
--------------------------

create table CALENDAR_OBJECT_SPLITTER_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  RESOURCE_ID                   integer      not null references CALENDAR_OBJECT on delete cascade
);

create index CALENDAR_OBJECT_SPLITTER_WORK_RESOURCE_ID on
  CALENDAR_OBJECT_SPLITTER_WORK(RESOURCE_ID);
create index CALENDAR_OBJECT_SPLITTER_WORK_JOB_ID on
  CALENDAR_OBJECT_SPLITTER_WORK(JOB_ID);

-------------------------
-- Object Upgrade Work --
-------------------------

create table CALENDAR_OBJECT_UPGRADE_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  RESOURCE_ID                   integer      not null references CALENDAR_OBJECT on delete cascade
);

create index CALENDAR_OBJECT_UPGRADE_WORK_RESOURCE_ID on
  CALENDAR_OBJECT_UPGRADE_WORK(RESOURCE_ID);
create index CALENDAR_OBJECT_UPGRADE_WORK_JOB_ID on
  CALENDAR_OBJECT_UPGRADE_WORK(JOB_ID);

---------------------------
-- Revision Cleanup Work --
---------------------------

create table FIND_MIN_VALID_REVISION_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index FIND_MIN_VALID_REVISION_WORK_JOB_ID on
  FIND_MIN_VALID_REVISION_WORK(JOB_ID);

create table REVISION_CLEANUP_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index REVISION_CLEANUP_WORK_JOB_ID on
  REVISION_CLEANUP_WORK(JOB_ID);

------------------------
-- Inbox Cleanup Work --
------------------------

create table INBOX_CLEANUP_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index INBOX_CLEANUP_WORK_JOB_ID on
   INBOX_CLEANUP_WORK(JOB_ID);

create table CLEANUP_ONE_INBOX_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  HOME_ID                       integer      not null unique references CALENDAR_HOME on delete cascade -- implicit index
);

create index CLEANUP_ONE_INBOX_WORK_JOB_ID on
  CLEANUP_ONE_INBOX_WORK(JOB_ID);

create table INBOX_REMOVE_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  HOME_ID                       integer      not null references CALENDAR_HOME on delete cascade,
  RESOURCE_NAME                 varchar(255) not null,

  unique (HOME_ID, RESOURCE_NAME)    -- implicit index
);

create index INBOX_REMOVE_WORK_JOB_ID on
  INBOX_REMOVE_WORK(JOB_ID);

-------------------
-- Schedule Work --
-------------------

create table SCHEDULE_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  ICALENDAR_UID                 varchar(255) not null,
  WORK_TYPE                     varchar(255) not null
);

create index SCHEDULE_WORK_JOB_ID on
  SCHEDULE_WORK(JOB_ID);
create index SCHEDULE_WORK_ICALENDAR_UID on
  SCHEDULE_WORK(ICALENDAR_UID);

---------------------------
-- Schedule Refresh Work --
---------------------------

create table SCHEDULE_REFRESH_WORK (
  WORK_ID                       integer      primary key references SCHEDULE_WORK on delete cascade, -- implicit index
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade,
  RESOURCE_ID                   integer      not null references CALENDAR_OBJECT on delete cascade,
  ATTENDEE_COUNT                integer
);

create index SCHEDULE_REFRESH_WORK_HOME_RESOURCE_ID on
  SCHEDULE_REFRESH_WORK(HOME_RESOURCE_ID);
create index SCHEDULE_REFRESH_WORK_RESOURCE_ID on
  SCHEDULE_REFRESH_WORK(RESOURCE_ID);

create table SCHEDULE_REFRESH_ATTENDEES (
  RESOURCE_ID                   integer      not null references CALENDAR_OBJECT on delete cascade,
  ATTENDEE                      varchar(255) not null,

  primary key (RESOURCE_ID, ATTENDEE)
);

------------------------------
-- Schedule Auto Reply Work --
------------------------------

create table SCHEDULE_AUTO_REPLY_WORK (
  WORK_ID                       integer      primary key references SCHEDULE_WORK on delete cascade, -- implicit index
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade,
  RESOURCE_ID                   integer      not null references CALENDAR_OBJECT on delete cascade,
  PARTSTAT                      varchar(255) not null
);

create index SCHEDULE_AUTO_REPLY_WORK_HOME_RESOURCE_ID on
  SCHEDULE_AUTO_REPLY_WORK(HOME_RESOURCE_ID);
create index SCHEDULE_AUTO_REPLY_WORK_RESOURCE_ID on
  SCHEDULE_AUTO_REPLY_WORK(RESOURCE_ID);

-----------------------------
-- Schedule Organizer Work --
-----------------------------

create table SCHEDULE_ORGANIZER_WORK (
  WORK_ID                       integer      primary key references SCHEDULE_WORK on delete cascade, -- implicit index
  SCHEDULE_ACTION               integer      not null, -- Enum SCHEDULE_ACTION
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade,
  RESOURCE_ID                   integer,     -- this references a possibly non-existent CALENDAR_OBJECT
  ICALENDAR_TEXT_OLD            text,
  ICALENDAR_TEXT_NEW            text,
  ATTENDEE_COUNT                integer,
  SMART_MERGE                   boolean
);

create index SCHEDULE_ORGANIZER_WORK_HOME_RESOURCE_ID on
  SCHEDULE_ORGANIZER_WORK(HOME_RESOURCE_ID);
create index SCHEDULE_ORGANIZER_WORK_RESOURCE_ID on
  SCHEDULE_ORGANIZER_WORK(RESOURCE_ID);

-- Enumeration of schedule actions

create table SCHEDULE_ACTION (
  ID          integer     primary key,
  DESCRIPTION varchar(16) not null unique
);

insert into SCHEDULE_ACTION values (0, 'create');
insert into SCHEDULE_ACTION values (1, 'modify');
insert into SCHEDULE_ACTION values (2, 'modify-cancelled');
insert into SCHEDULE_ACTION values (3, 'remove');

----------------------------------
-- Schedule Organizer Send Work --
----------------------------------

create table SCHEDULE_ORGANIZER_SEND_WORK (
  WORK_ID                       integer      primary key references SCHEDULE_WORK on delete cascade, -- implicit index
  SCHEDULE_ACTION               integer      not null, -- Enum SCHEDULE_ACTION
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade,
  RESOURCE_ID                   integer,     -- this references a possibly non-existent CALENDAR_OBJECT
  ATTENDEE                      varchar(255) not null,
  ITIP_MSG                      text,
  NO_REFRESH                    boolean
);

create index SCHEDULE_ORGANIZER_SEND_WORK_HOME_RESOURCE_ID on
  SCHEDULE_ORGANIZER_SEND_WORK(HOME_RESOURCE_ID);
create index SCHEDULE_ORGANIZER_SEND_WORK_RESOURCE_ID on
  SCHEDULE_ORGANIZER_SEND_WORK(RESOURCE_ID);

-------------------------
-- Schedule Reply Work --
-------------------------

create table SCHEDULE_REPLY_WORK (
  WORK_ID                       integer      primary key references SCHEDULE_WORK on delete cascade, -- implicit index
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade,
  RESOURCE_ID                   integer,     -- this references a possibly non-existent CALENDAR_OBJECT
  ITIP_MSG                      text
);

create index SCHEDULE_REPLY_WORK_HOME_RESOURCE_ID on
  SCHEDULE_REPLY_WORK(HOME_RESOURCE_ID);
create index SCHEDULE_REPLY_WORK_RESOURCE_ID on
  SCHEDULE_REPLY_WORK(RESOURCE_ID);

----------------------------------
-- Principal Purge Polling Work --
----------------------------------

create table PRINCIPAL_PURGE_POLLING_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null
);

create index PRINCIPAL_PURGE_POLLING_WORK_JOB_ID on
  PRINCIPAL_PURGE_POLLING_WORK(JOB_ID);

--------------------------------
-- Principal Purge Check Work --
--------------------------------

create table PRINCIPAL_PURGE_CHECK_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  UID                           varchar(255) not null
);

create index PRINCIPAL_PURGE_CHECK_WORK_JOB_ID on
  PRINCIPAL_PURGE_CHECK_WORK(JOB_ID);
create index PRINCIPAL_PURGE_CHECK_WORK_UID on
  PRINCIPAL_PURGE_CHECK_WORK(UID);

--------------------------
-- Principal Purge Work --
--------------------------

create table PRINCIPAL_PURGE_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  UID                           varchar(255) not null
);

create index PRINCIPAL_PURGE_WORK_JOB_ID on
  PRINCIPAL_PURGE_WORK(JOB_ID);
create index PRINCIPAL_PURGE_WORK_UID on
  PRINCIPAL_PURGE_WORK(UID);


--------------------------------
-- Principal Home Remove Work --
--------------------------------

create table PRINCIPAL_PURGE_HOME_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade
);

create index PRINCIPAL_PURGE_HOME_WORK_JOB_ID on
  PRINCIPAL_PURGE_HOME_WORK(JOB_ID);
create index PRINCIPAL_PURGE_HOME_HOME_RESOURCE_ID on
  PRINCIPAL_PURGE_HOME_WORK(HOME_RESOURCE_ID);


----------------------------
-- Migration Cleanup Work --
----------------------------

create table MIGRATION_CLEANUP_WORK (
  WORK_ID                       integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID                        integer      references JOB not null,
  HOME_RESOURCE_ID              integer      not null references CALENDAR_HOME on delete cascade
);

create index MIGRATION_CLEANUP_WORK_JOB_ID on
  MIGRATION_CLEANUP_WORK(JOB_ID);
create index MIGRATION_CLEANUP_WORK_HOME_RESOURCE_ID on
  MIGRATION_CLEANUP_WORK(HOME_RESOURCE_ID);

-----------------------
-- Home Cleanup Work --
-----------------------

create table HOME_CLEANUP_WORK (
  WORK_ID          integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID           integer      references JOB not null,
  OWNER_UID        varchar(255) not null
);

create index HOME_CLEANUP_WORK_JOB_ID on
  HOME_CLEANUP_WORK(JOB_ID);

--------------------------------
-- Migrated Home Cleanup Work --
--------------------------------

create table MIGRATED_HOME_CLEANUP_WORK (
  WORK_ID          integer      primary key default nextval('WORKITEM_SEQ'), -- implicit index
  JOB_ID           integer      references JOB not null,
  OWNER_UID        varchar(255) not null
);

create index MIGRATED_HOME_CLEANUP_WORK_JOB_ID on
  MIGRATED_HOME_CLEANUP_WORK(JOB_ID);

--------------------
-- Schema Version --
--------------------

create table CALENDARSERVER (
  NAME                          varchar(255) primary key, -- implicit index
  VALUE                         varchar(255)
);

insert into CALENDARSERVER values ('VERSION', '63');
insert into CALENDARSERVER values ('CALENDAR-DATAVERSION', '6');
insert into CALENDARSERVER values ('ADDRESSBOOK-DATAVERSION', '2');
insert into CALENDARSERVER values ('NOTIFICATION-DATAVERSION', '1');
insert into CALENDARSERVER values ('MIN-VALID-REVISION', '1');
