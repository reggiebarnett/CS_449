//Reggie Barnett
//Project 4
//Dice Driver

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/random.h>

ssize_t dice_driver_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos);
int dice_driver_init(void);
void dice_driver_exit(void);
unsigned char get_random_byte(int);

static const struct file_operations dice_driver_fops = {
	.read		= dice_driver_read,
};

module_init(dice_driver_init);
module_exit(dice_driver_exit);

int dice_roll;

struct miscdevice dice_driver_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/hello.
	 */
	"dice",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&dice_driver_fops
};

int dice_driver_init(void)
{
	int ret;
	/*Create the "dice_driver" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/hello device using
	 * the default rules.*/
	ret = misc_register(&dice_driver_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"Dice Driver\" misc device\n");
	return ret;
}

dice_driver_exit(void)
{
	misc_deregister(&dice_driver_dev);
}

ssize_t dice_driver_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	if(count%sizeof(int)==0){
		dice_roll = get_random_byte(6)+1;
		copy_to_user(buf,&dice_roll,count);	
		return count;
	}
	else{
		printk("<1> Invalid bytes to read");
		return -1;
	}
}

unsigned char get_random_byte(int max) {
         unsigned char c;
         get_random_bytes(&c, 1);
         return c%max;
}


MODULE_LICENSE("GPL");

