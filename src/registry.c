#include "registry.h"

File_base_bloc *read_file_base_bloc(char *buf)
{
	/*
		Read the file base bloc, alloc
		a new file base bloc srtucture
		and fill it with the value in
		buf string
	*/

	File_base_bloc *fbc;

	fbc = NULL;

	fbc = (File_base_bloc*) malloc(sizeof(File_base_bloc));
	if(fbc == NULL)
	{
		printf("Error d'allocation de fbc\n");
		return NULL;
	}

	bzero(fbc, sizeof(File_base_bloc));

	strncpy(fbc->signature, buf, 4);
	fill_int(&(fbc->primary_seq_number), &buf[4]);
	fill_int(&(fbc->secondary_seq_number), &buf[8]);
	fill_long(&(fbc->last_written_timestamp), &buf[12]);
	fill_int(&(fbc->major_version), &buf[20]);
	fill_int(&(fbc->minor_version), &buf[24]);
	fill_int(&(fbc->file_type), &buf[28]);
	fill_int(&(fbc->file_format), &buf[32]);
	fill_int(&(fbc->root_cell_offset), &buf[36]);
	fill_int(&(fbc->hive_bin_data_size), &buf[40]);
	fill_int(&(fbc->clustering_factor), &buf[44]);
	strncpy(fbc->filename, &buf[48], 64);
	strncpy(fbc->reserved, &buf[112], 396);
	fill_int(&(fbc->checksum), &buf[508]);
	strncpy(fbc->reserved2, &buf[512], 3576);
	fill_int(&(fbc->boot_type), &buf[4088]);
	fill_int(&(fbc->boot_recover), &buf[4092]);

	return fbc;
}

Hive_bin_header *read_hive_bin_header(char *buf)
{
	/*
		Read the hive bin header, alloc
		a new hive bin header srtucture
		and fill it with the value in
		buf string
	*/

	Hive_bin_header *hbh;

	hbh = NULL;

	hbh = (Hive_bin_header*) malloc(sizeof(Hive_bin_header));
	if(hbh == NULL)
	{
		printf("Error d'allocation de hbh\n");
		return NULL;
	}

	bzero(hbh, sizeof(Hive_bin_header));

	strncpy(hbh->signature, buf, 4);
	fill_int(&(hbh->offset), &buf[4]);
	fill_int(&(hbh->size), &buf[8]);
	strncpy(hbh->reserved, &buf[12], 8);
	fill_long(&(hbh->timestamp), &buf[20]);
	fill_int(&(hbh->spare), &buf[28]);

	return hbh;
}

int nb_to_read(char *buf)
{
	/*
		Return the number of Bytes to read
		in function of the signatures
	*/
	if(strncmp(buf, "regf", 4) == 0)
		return 4096;
	else if(strncmp(buf, "hbin", 4) == 0)
		return 32;

	return 0;
}

void fill_int(int *i, char *buf)
{
	/*
		Fill int from buf
	*/

	*i = buf[3] & 0xFF;
	*i = ((*i) << 8) + (buf[2] & 0xFF);
	*i = ((*i) << 8) + (buf[1] & 0xFF);
	*i = ((*i) << 8) + (buf[0] & 0xFF);
}

void fill_long(long *l, char *buf)
{
	/*
		Fill long from buf
	*/

	*l = buf[7] & 0xFF;
	*l = ((*l) << 8) + (buf[6] & 0xFF);
	*l = ((*l) << 8) + (buf[5] & 0xFF);
	*l = ((*l) << 8) + (buf[4] & 0xFF);
	*l = ((*l) << 8) + (buf[3] & 0xFF);
	*l = ((*l) << 8) + (buf[2] & 0xFF);
	*l = ((*l) << 8) + (buf[1] & 0xFF);
	*l = ((*l) << 8) + (buf[0] & 0xFF);

}
