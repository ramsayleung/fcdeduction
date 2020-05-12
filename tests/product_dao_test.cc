#include "src/dal/product_dao.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/product.h"

TEST(DAOTEST, PRODUCT_EXIST_TEST) {
  const std::string pdCode = "pdCode1000";
  const std::string tntInstId = "A0000001";
  fcdeduction::dataobject::Product product;
  product.gmtCreate = std::chrono::system_clock::now();
  product.gmtModified = std::chrono::system_clock::now();
  product.memo = "memo";
  product.pdName = "test product";
  product.pdDesc = "test product desc";
  product.pdOrgName = "test product org";
  product.pdCode = pdCode;
  product.tntInstId = tntInstId;

  fcdeduction::dao::ProductDao productDao;
  productDao.deleteProductByPdCode(tntInstId, pdCode);
  productDao.insertProduct(product);
  EXPECT_TRUE(productDao.productExist(tntInstId, pdCode));
  productDao.deleteProductByPdCode(tntInstId, pdCode);
}