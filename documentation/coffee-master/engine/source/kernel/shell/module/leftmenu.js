function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6327\" class=\"headerLeftMenuInActive\"><a id=\"aID6327\" href=\"#\" OnMouseOver=\"link('_dir','module0',this)\" class=\"leftMenuLinkHeadInActive\">module</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID814\" class=\"leftMenuInActive\"><a id=\"aID814\" href=\"#\" OnMouseOver=\"link('_class','Module41582',this)\" class=\"leftMenuLinkInActive\">Module</a></div>\n");
document.write("<div id=\"divID815\" class=\"leftMenuInActive\"><a id=\"aID815\" href=\"#\" OnMouseOver=\"link('_class','ModuleConfig41582',this)\" class=\"leftMenuLinkInActive\">ModuleConfig</a></div>\n");
document.write("<div id=\"divID816\" class=\"leftMenuInActive\"><a id=\"aID816\" href=\"#\" OnMouseOver=\"link('_class','ModuleManager41582',this)\" class=\"leftMenuLinkInActive\">ModuleManager</a></div>\n");
document.write("<div id=\"divID817\" class=\"leftMenuInActive\"><a id=\"aID817\" href=\"#\" OnMouseOver=\"link('_class','ModuleManagerConfig41582',this)\" class=\"leftMenuLinkInActive\">ModuleManagerConfig</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6221\" class=\"leftMenuInActive\"><a id=\"aID6221\" href=\"#\" OnMouseOver=\"link('_member','MODULE_ATTRIBUTE18069215',this)\" class=\"leftMenuLinkInActive\">MODULE_ATTRIBUTE</a></div>\n");
document.write("<div id=\"divID6222\" class=\"leftMenuInActive\"><a id=\"aID6222\" href=\"#\" OnMouseOver=\"link('_member','MODULE_EVENT18069215',this)\" class=\"leftMenuLinkInActive\">MODULE_EVENT</a></div>\n");
document.write("<div id=\"divID6223\" class=\"leftMenuInActive\"><a id=\"aID6223\" href=\"#\" OnMouseOver=\"link('_member','MODULE_STATE18069215',this)\" class=\"leftMenuLinkInActive\">MODULE_STATE</a></div>\n");
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
