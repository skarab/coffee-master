function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6437\" class=\"headerLeftMenuInActive\"><a id=\"aID6437\" href=\"#\" OnMouseOver=\"link('_dir','scalar0',this)\" class=\"leftMenuLinkHeadInActive\">scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID978\" class=\"leftMenuInActive\"><a id=\"aID978\" href=\"#\" OnMouseOver=\"link('_class','PropertyBool49249',this)\" class=\"leftMenuLinkInActive\">PropertyBool</a></div>\n");
document.write("<div id=\"divID979\" class=\"leftMenuInActive\"><a id=\"aID979\" href=\"#\" OnMouseOver=\"link('_class','PropertyEnum49249',this)\" class=\"leftMenuLinkInActive\">PropertyEnum</a></div>\n");
document.write("<div id=\"divID980\" class=\"leftMenuInActive\"><a id=\"aID980\" href=\"#\" OnMouseOver=\"link('_class','PropertyInt1649249',this)\" class=\"leftMenuLinkInActive\">PropertyInt16</a></div>\n");
document.write("<div id=\"divID981\" class=\"leftMenuInActive\"><a id=\"aID981\" href=\"#\" OnMouseOver=\"link('_class','PropertyInt3249249',this)\" class=\"leftMenuLinkInActive\">PropertyInt32</a></div>\n");
document.write("<div id=\"divID982\" class=\"leftMenuInActive\"><a id=\"aID982\" href=\"#\" OnMouseOver=\"link('_class','PropertyInt849249',this)\" class=\"leftMenuLinkInActive\">PropertyInt8</a></div>\n");
document.write("<div id=\"divID983\" class=\"leftMenuInActive\"><a id=\"aID983\" href=\"#\" OnMouseOver=\"link('_class','PropertyReal49249',this)\" class=\"leftMenuLinkInActive\">PropertyReal</a></div>\n");
document.write("<div id=\"divID984\" class=\"leftMenuInActive\"><a id=\"aID984\" href=\"#\" OnMouseOver=\"link('_class','PropertyScalar26365',this)\" class=\"leftMenuLinkInActive\">PropertyScalar<></a></div>\n");
document.write("<div id=\"divID985\" class=\"leftMenuInActive\"><a id=\"aID985\" href=\"#\" OnMouseOver=\"link('_class','PropertyUInt1649249',this)\" class=\"leftMenuLinkInActive\">PropertyUInt16</a></div>\n");
document.write("<div id=\"divID986\" class=\"leftMenuInActive\"><a id=\"aID986\" href=\"#\" OnMouseOver=\"link('_class','PropertyUInt3249249',this)\" class=\"leftMenuLinkInActive\">PropertyUInt32</a></div>\n");
document.write("<div id=\"divID987\" class=\"leftMenuInActive\"><a id=\"aID987\" href=\"#\" OnMouseOver=\"link('_class','PropertyUInt32EnumMulti49249',this)\" class=\"leftMenuLinkInActive\">PropertyUInt32EnumMulti</a></div>\n");
document.write("<div id=\"divID988\" class=\"leftMenuInActive\"><a id=\"aID988\" href=\"#\" OnMouseOver=\"link('_class','PropertyUInt849249',this)\" class=\"leftMenuLinkInActive\">PropertyUInt8</a></div>\n");
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
