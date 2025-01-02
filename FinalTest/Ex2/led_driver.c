// Tran Vu Hong Phuc - 21ES - 123210021
// Ex2 - LED Driver using descriptor-based GPIO Interface

#include <linux/module.h>
#include <linux/gpio/consumer.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

// Data Structures

static struct gpio_desc *led_gpio;  // GPIO descriptor for controlling the LED
static struct timer_list led_blink_timer;  // Timer for scheduling LED blinking

// Define the LED blink interval in 1000ms
#define BLINK_INTERVAL_MS 1000

// Character device variables
static dev_t led_dev; // The device number
static struct cdev c_dev; // The character device structure

// Define ioctl commands for controlling blinking
#define LED_BLINK_START _IO('q', 1) // Command to start blinking the LED
#define LED_BLINK_STOP _IO('q', 2)  // Command to stop blinking the LED

static bool blinking_enabled = false; // Flag to track blinking state

// Toggle LED state and reschedule the timer
static void led_blink_function(struct timer_list *t) {
    static bool led_state = false;// Tracks the current state of the LED (on/off)

    if (blinking_enabled) {
        gpiod_set_value(led_gpio, led_state);
        led_state = !led_state; // Toggle LED state
        // Reschedule the timer for the next blink interval
        mod_timer(&led_blink_timer, jiffies + msecs_to_jiffies(BLINK_INTERVAL_MS));
    }
}
// File operation: Open the LED driver
static int led_open(struct inode *i, struct file *f) {
    return 0; // No special actions required during open
}
// File operation: Close the LED driver
static int led_close(struct inode *i, struct file *f) {
    return 0; // No special actions required during close
}

// IOCTL handler for starting and stopping LED blinking
static long led_ioctl(struct file *f, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case LED_BLINK_START:
            blinking_enabled = true;// Enable blinking
            // Start the timer to toggle the LED
            mod_timer(&led_blink_timer, jiffies + msecs_to_jiffies(BLINK_INTERVAL_MS));
            break;

        case LED_BLINK_STOP:
            blinking_enabled = false;
            del_timer_sync(&led_blink_timer);
            gpiod_set_value(led_gpio, 0); // Turn off the LED
            break;

        default:
            return -ENOTTY; // Command not supported
    }
    return 0;
}

// Link operations to the character device
static struct file_operations fops = {
    .open = led_open, // Open handler
    .release = led_close, // Close handler
    .unlocked_ioctl = led_ioctl, // IOCTL handler
};

// Initialize the LED driver module
static int __init led_driver_init(void) {
    int ret;

    // Allocate character device region
    if (alloc_chrdev_region(&led_dev, 0, 1, "led_driver") < 0) {
        return -1;
    }

    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, led_dev, 1) == -1) {
        unregister_chrdev_region(led_dev, 1);
        return -1;
    }

    // Acquire GPIO descriptor
    led_gpio = gpiod_get(NULL, "led", GPIOD_OUT_LOW);
    if (IS_ERR(led_gpio)) {
        cdev_del(&c_dev);
        unregister_chrdev_region(led_dev, 1);
        return PTR_ERR(led_gpio);
    }

    // Initialize the timer
    timer_setup(&led_blink_timer, led_blink_function, 0);

    pr_info("LED Driver initialized successfully\n");
    return 0;
}

// Cleanup resources
static void __exit led_driver_exit(void) {
    del_timer(&led_blink_timer);
    gpiod_put(led_gpio);

    cdev_del(&c_dev);
    unregister_chrdev_region(led_dev, 1);

    pr_info("LED Driver exited successfully\n");
}

module_init(led_driver_init);
module_exit(led_driver_exit);

// Metadata about the module
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phuc");
MODULE_DESCRIPTION("LED Blinking Driver using descriptor-based GPIO Interface");
