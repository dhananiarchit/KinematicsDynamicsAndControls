function mrdplot_open(flag)
% open and reads in a file

global MRDS;

% for flag==1, we try to read the filename from the file last_data

fname =[];

if exist('last_data') & flag == 1,
	fid = fopen('last_data','r');
	fileid = fscanf(fid,'%d');
	last_data = sprintf('d%05d',fileid-1);
	fclose(fid);
	if exist(last_data),
		fname = last_data;
		pathname=' ';
	end;
end;

% read in the file name
if isempty(fname),
	[fname, pathname] = uigetfile('*','Select Data File');
	if (fname == 0),
		return;
	end;
end;

% concatenate pathname and filename and open file
fname_store = fname;
fname=strcat(pathname, fname);
fid=fopen(fname, 'r','ieee-be');
if fid == -1,
	return;
end;

specs=fscanf(fid,'%d %d %d %f',4);  % [dummy,cols,rows,freq]
MRDS.cols = specs(2);
MRDS.rows = specs(3);
MRDS.freq = specs(4);
MRDS.t    = (1:MRDS.rows)'/MRDS.freq;  % the time column
MRDS.vars = [];
MRDS.fname= fname;

% read all variable names

for i=1:MRDS.cols,
	MRDS.vars(i).name=fscanf(fid,'%s',1);
	MRDS.vars(i).unit=fscanf(fid,'%s',1);
end;
fscanf(fid,'%c',3); % there are three characters which must be skipped

% read the data
MRDS.data = fread(fid, [MRDS.cols,MRDS.rows],'float32');
MRDS.data=MRDS.data';
fclose(fid);

% build the string for showing the variable names

temp = sprintf('%s [%s]',MRDS.vars(1).name,MRDS.vars(1).unit);
string=sprintf('%20s= %% .4g',temp);
for i=2:MRDS.cols,
	temp = sprintf('%s [%s]',MRDS.vars(i).name,MRDS.vars(i).unit);
	string=[string,'|',sprintf('%20s= %% .4g',temp)];
end;

MRDS.string=string;
set(MRDS.lptr,'Value',1,'String',sprintf(MRDS.string,MRDS.data(1,:)));
MRDS.cursor = 1;
set(MRDS.tptr,'String',sprintf('time=%8.4f  tick=%5d',MRDS.t(MRDS.cursor),MRDS.cursor));

% fix all plots

mrdplot_update_subplots;

% write the file name

set(MRDS.nptr,'String',sprintf('Variables of %s',fname_store));
