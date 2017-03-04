function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6289\" class=\"headerLeftMenuInActive\"><a id=\"aID6289\" href=\"#\" OnMouseOver=\"link('_dir','property0',this)\" class=\"leftMenuLinkHeadInActive\">property</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID751\" class=\"leftMenuInActive\"><a id=\"aID751\" href=\"#\" OnMouseOver=\"link('_class','Property6216',this)\" class=\"leftMenuLinkInActive\">Property<></a></div>\n");
document.write("<div id=\"divID752\" class=\"leftMenuInActive\"><a id=\"aID752\" href=\"#\" OnMouseOver=\"link('_class','PropertyBase39014',this)\" class=\"leftMenuLinkInActive\">PropertyBase</a></div>\n");
document.write("<div id=\"divID753\" class=\"leftMenuInActive\"><a id=\"aID753\" href=\"#\" OnMouseOver=\"link('_class','PropertyList39014',this)\" class=\"leftMenuLinkInActive\">PropertyList</a></div>\n");
document.write("<div id=\"divID754\" class=\"leftMenuInActive\"><a id=\"aID754\" href=\"#\" OnMouseOver=\"link('_class','PropertyScalar39014',this)\" class=\"leftMenuLinkInActive\">PropertyScalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1194\" class=\"leftMenuInActive\"><a id=\"aID1194\" href=\"#\" OnMouseOver=\"link('_member','Property7578827',this)\" class=\"leftMenuLinkInActive\">Property</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6210\" class=\"leftMenuInActive\"><a id=\"aID6210\" href=\"#\" OnMouseOver=\"link('_member','PROPERTY_FLAG7578827',this)\" class=\"leftMenuLinkInActive\">PROPERTY_FLAG</a></div>\n");
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
