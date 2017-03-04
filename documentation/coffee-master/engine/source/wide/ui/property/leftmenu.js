function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6438\" class=\"headerLeftMenuInActive\"><a id=\"aID6438\" href=\"#\" OnMouseOver=\"link('_dir','property0',this)\" class=\"leftMenuLinkHeadInActive\">property</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6433\" class=\"leftMenuInActive\"><a id=\"aID6433\" href=\"#\" OnMouseOver=\"link('_dir','array/array0',this)\" class=\"leftMenuLinkInActive\">array</a></div>\n");
document.write("<div id=\"divID6435\" class=\"leftMenuInActive\"><a id=\"aID6435\" href=\"#\" OnMouseOver=\"link('_dir','basic/basic0',this)\" class=\"leftMenuLinkInActive\">basic</a></div>\n");
document.write("<div id=\"divID6436\" class=\"leftMenuInActive\"><a id=\"aID6436\" href=\"#\" OnMouseOver=\"link('_dir','resource/resource0',this)\" class=\"leftMenuLinkInActive\">resource</a></div>\n");
document.write("<div id=\"divID6437\" class=\"leftMenuInActive\"><a id=\"aID6437\" href=\"#\" OnMouseOver=\"link('_dir','scalar/scalar0',this)\" class=\"leftMenuLinkInActive\">scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID989\" class=\"leftMenuInActive\"><a id=\"aID989\" href=\"#\" OnMouseOver=\"link('_class','Property49249',this)\" class=\"leftMenuLinkInActive\">Property</a></div>\n");
document.write("<div id=\"divID990\" class=\"leftMenuInActive\"><a id=\"aID990\" href=\"#\" OnMouseOver=\"link('_class','PropertyList49249',this)\" class=\"leftMenuLinkInActive\">PropertyList</a></div>\n");
document.write("<div id=\"divID991\" class=\"leftMenuInActive\"><a id=\"aID991\" href=\"#\" OnMouseOver=\"link('_class','PropertyManager49249',this)\" class=\"leftMenuLinkInActive\">PropertyManager</a></div>\n");
document.write("<div id=\"divID992\" class=\"leftMenuInActive\"><a id=\"aID992\" href=\"#\" OnMouseOver=\"link('_class','PropertyUndo49249',this)\" class=\"leftMenuLinkInActive\">PropertyUndo</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6235\" class=\"leftMenuInActive\"><a id=\"aID6235\" href=\"#\" OnMouseOver=\"link('_member','PROPERTY_FLAG121877613',this)\" class=\"leftMenuLinkInActive\">PROPERTY_FLAG</a></div>\n");
document.write("<div id=\"divID6236\" class=\"leftMenuInActive\"><a id=\"aID6236\" href=\"#\" OnMouseOver=\"link('_member','PROPERTY_MESSAGE121877613',this)\" class=\"leftMenuLinkInActive\">PROPERTY_MESSAGE</a></div>\n");
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
