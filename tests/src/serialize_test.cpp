#include "gtest/gtest.h"
#include "types.h"
#include "hw/_vmem.h"
#include "hw/maple_cfg.h"
#include "hw/maple_devs.h"
#include "emulator.h"
#include "cfg/option.h"

class SerializeTest : public ::testing::Test {
protected:
	void SetUp() override {
		if (!_vmem_reserve())
			die("_vmem_reserve failed");
		dc_init();
		dc_reset(true);
	}
};

TEST_F(SerializeTest, SizeTest)
{
	using namespace config;
	Settings::instance().reset();
	MapleMainDevices[0] = MDT_SegaController;
	MapleExpansionDevices[0][0] = MDT_SegaVMU;
	MapleExpansionDevices[0][1] = MDT_SegaVMU;
	MapleMainDevices[1] = MDT_SegaController;
	MapleExpansionDevices[1][0] = MDT_SegaVMU;
	MapleExpansionDevices[1][1] = MDT_SegaVMU;
	mcfg_CreateDevices();

	unsigned int total_size = 0;
	void *data = nullptr;
	ASSERT_TRUE(dc_serialize(&data, &total_size));
	ASSERT_EQ(28145503u, total_size);
}



