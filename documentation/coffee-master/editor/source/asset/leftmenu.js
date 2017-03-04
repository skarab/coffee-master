function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6467\" class=\"headerLeftMenuInActive\"><a id=\"aID6467\" href=\"#\" OnMouseOver=\"link('_dir','asset0',this)\" class=\"leftMenuLinkHeadInActive\">asset</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6468\" class=\"leftMenuInActive\"><a id=\"aID6468\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6469\" class=\"leftMenuInActive\"><a id=\"aID6469\" href=\"#\" OnMouseOver=\"link('_dir','font/font0',this)\" class=\"leftMenuLinkInActive\">font</a></div>\n");
document.write("<div id=\"divID6470\" class=\"leftMenuInActive\"><a id=\"aID6470\" href=\"#\" OnMouseOver=\"link('_dir','mesh/mesh0',this)\" class=\"leftMenuLinkInActive\">mesh</a></div>\n");
document.write("<div id=\"divID6471\" class=\"leftMenuInActive\"><a id=\"aID6471\" href=\"#\" OnMouseOver=\"link('_dir','plugin/plugin0',this)\" class=\"leftMenuLinkInActive\">plugin</a></div>\n");
document.write("<div id=\"divID6472\" class=\"leftMenuInActive\"><a id=\"aID6472\" href=\"#\" OnMouseOver=\"link('_dir','shader/shader0',this)\" class=\"leftMenuLinkInActive\">shader</a></div>\n");
document.write("<div id=\"divID6473\" class=\"leftMenuInActive\"><a id=\"aID6473\" href=\"#\" OnMouseOver=\"link('_dir','sound/sound0',this)\" class=\"leftMenuLinkInActive\">sound</a></div>\n");
document.write("<div id=\"divID6474\" class=\"leftMenuInActive\"><a id=\"aID6474\" href=\"#\" OnMouseOver=\"link('_dir','texture/texture0',this)\" class=\"leftMenuLinkInActive\">texture</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1047\" class=\"leftMenuInActive\"><a id=\"aID1047\" href=\"#\" OnMouseOver=\"link('_class','Importer22463',this)\" class=\"leftMenuLinkInActive\">Importer</a></div>\n");
document.write("<div id=\"divID1048\" class=\"leftMenuInActive\"><a id=\"aID1048\" href=\"#\" OnMouseOver=\"link('_class','Manager22463',this)\" class=\"leftMenuLinkInActive\">Manager</a></div>\n");
document.write("<div id=\"divID6193\" class=\"leftMenuInActive\"><a id=\"aID6193\" href=\"#\" OnMouseOver=\"link('_class','Object0',this)\" class=\"leftMenuLinkInActive\">Object</a></div>\n");
document.write("<div id=\"divID1049\" class=\"leftMenuInActive\"><a id=\"aID1049\" href=\"#\" OnMouseOver=\"link('_class','ResourceWidget22463',this)\" class=\"leftMenuLinkInActive\">ResourceWidget</a></div>\n");
document.write("<div id=\"divID1050\" class=\"leftMenuInActive\"><a id=\"aID1050\" href=\"#\" OnMouseOver=\"link('_class','Widget22463',this)\" class=\"leftMenuLinkInActive\">Widget</a></div>\n");
document.write("<div id=\"divID6173\" class=\"leftMenuInActive\"><a id=\"aID6173\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6259\" class=\"leftMenuInActive\"><a id=\"aID6259\" href=\"#\" OnMouseOver=\"link('_member','SYNC_FLAG1124631283',this)\" class=\"leftMenuLinkInActive\">SYNC_FLAG</a></div>\n");
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
