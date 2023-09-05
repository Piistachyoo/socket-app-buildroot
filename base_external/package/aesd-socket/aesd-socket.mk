
##############################################################
#
# AESD-SOCKET
#
##############################################################

#TODO: Fill up the contents below in order to reference your assignment 3 git contents
AESD_SOCKET_VERSION = 5a235e69cb07e65d2bc3dc928a95bc7b286ede03
# Note: Be sure to reference the *ssh* repository URL here (not https) to work properly
# with ssh keys and the automated build/test system.
# Your site should start with git@github.com:
AESD_SOCKET_SITE = git@github.com:cu-ecen-aeld/assignments-3-and-later-Piistachyoo.git
AESD_SOCKET_SITE_METHOD = git
AESD_SOCKET_GIT_SUBMODULES = YES

define AESD_SOCKET_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)/server all 
endef

# TODO add your writer, finder and finder-test utilities/scripts to the installation steps below
define AESD_SOCKET_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 $(@D)/server/aesdsocket $(TARGET_DIR)/usr/bin
	$(INSTALL) -m 0755 $(@D)/server/aesdsocket-start-stop $(TARGET_DIR)/etc/init.d/S99aesdsocket
	$(INSTALL) -m 0755 $(@D)/assignment-autotest/test/assignment5/* $(TARGET_DIR)/bin
endef

$(eval $(generic-package))

