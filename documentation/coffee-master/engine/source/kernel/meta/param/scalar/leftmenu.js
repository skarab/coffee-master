function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6308\" class=\"headerLeftMenuInActive\"><a id=\"aID6308\" href=\"#\" OnMouseOver=\"link('_dir','scalar0',this)\" class=\"leftMenuLinkHeadInActive\">scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID780\" class=\"leftMenuInActive\"><a id=\"aID780\" href=\"#\" OnMouseOver=\"link('_class','ParamScalar20541',this)\" class=\"leftMenuLinkInActive\">ParamScalar<></a></div>\n");
document.write("<div id=\"divID781\" class=\"leftMenuInActive\"><a id=\"aID781\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarInt1653261',this)\" class=\"leftMenuLinkInActive\">ParamScalarInt16</a></div>\n");
document.write("<div id=\"divID782\" class=\"leftMenuInActive\"><a id=\"aID782\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarInt3253261',this)\" class=\"leftMenuLinkInActive\">ParamScalarInt32</a></div>\n");
document.write("<div id=\"divID783\" class=\"leftMenuInActive\"><a id=\"aID783\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarInt853261',this)\" class=\"leftMenuLinkInActive\">ParamScalarInt8</a></div>\n");
document.write("<div id=\"divID784\" class=\"leftMenuInActive\"><a id=\"aID784\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarReal53261',this)\" class=\"leftMenuLinkInActive\">ParamScalarReal</a></div>\n");
document.write("<div id=\"divID785\" class=\"leftMenuInActive\"><a id=\"aID785\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarUInt1653261',this)\" class=\"leftMenuLinkInActive\">ParamScalarUInt16</a></div>\n");
document.write("<div id=\"divID786\" class=\"leftMenuInActive\"><a id=\"aID786\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarUInt3253261',this)\" class=\"leftMenuLinkInActive\">ParamScalarUInt32</a></div>\n");
document.write("<div id=\"divID787\" class=\"leftMenuInActive\"><a id=\"aID787\" href=\"#\" OnMouseOver=\"link('_class','ParamScalarUInt853261',this)\" class=\"leftMenuLinkInActive\">ParamScalarUInt8</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
